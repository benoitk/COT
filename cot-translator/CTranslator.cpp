#include "CTranslator.h"

#include <QStringList>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>

/* Memo of translatable properties
 * - root (name) - json object
 * - extensions (name) - json array of objects
 * - units (name) - json array of objects
 * - variables (name) - json array of objects
 * - streams (name) - json array of objects
 *  - measures (name) - json array of objects
 * - actions (name) - json array of objects
 *  - steps (name) - json array of objects
 * - cycles (name) - json array of objects
 *  - steps (name) - json array of objects
 * Streams and Measures do normally not have names, but as it's needed for translations
 * we will argue, names are auto generated for those classes and that the technician don't care about them.
*/

namespace {
const QStringList SUPPORTED_LOCALES = QStringList()
        << QLocale(QLocale::French, QLocale::AnyCountry).name()
        << QLocale(QLocale::English, QLocale::AnyCountry).name()
        << QLocale(QLocale::Russian, QLocale::AnyCountry).name()
        << QLocale(QLocale::Spanish, QLocale::AnyCountry).name()
        << QLocale(QLocale::Portuguese, QLocale::Portugal).name() // AnyCountry set Brazil as official country for Portuguese...
        << QLocale(QLocale::Chinese, QLocale::AnyCountry).name()
;
}

CTranslator::CTranslator(QObject *parent)
    : QObject(parent)
{
}

bool CTranslator::exportFrom(const QJsonDocument &jsonDocument, const QString &qmOutputPath)
{
    QDir dir;

    if (jsonDocument.isEmpty()) {
        qDebug("%s: The json document is empty", Q_FUNC_INFO);
        return false;
    }

    if (!dir.mkpath(qmOutputPath)) {
        qDebug("%s: Can't create path: %s", Q_FUNC_INFO, qPrintable(qmOutputPath));
        return false;
    }

    return doExport(jsonDocument, qmOutputPath);
}

bool CTranslator::exportFrom(const QString &jsonFilePath, const QString &qmOutputPath)
{
    if (!QFile::exists(jsonFilePath)) {
        qDebug("%s: The json file does not exists: %s", Q_FUNC_INFO, qPrintable(jsonFilePath));
        return false;
    }

    return exportFrom(createDocument(jsonFilePath), qmOutputPath);
}

bool CTranslator::importFrom(const QString &qmOutputPath, QJsonDocument &jsonDocument)
{
    if (jsonDocument.isEmpty()) {
        qDebug("%s: The json document is empty", Q_FUNC_INFO);
        return false;
    }

    if (!QFile::exists(qmOutputPath)) {
        qDebug("%s: Can't check path: %s", Q_FUNC_INFO, qPrintable(qmOutputPath));
        return false;
    }

    return doImport(jsonDocument, qmOutputPath);
}

bool CTranslator::importFrom(const QString &qmOutputPath, const QString &jsonFilePath)
{
    if (!QFile::exists(jsonFilePath)) {
        qDebug("%s: The json file does not exists: %s", Q_FUNC_INFO, qPrintable(jsonFilePath));
        return false;
    }

    QJsonDocument jsonDocument = createDocument(jsonFilePath);

    if (importFrom(qmOutputPath, jsonDocument)) {
        return saveDocument(jsonDocument, jsonFilePath);
    }

    return false;
}

QString CTranslator::translationsFilePath(const QString &qmOutputPath, const QString &locale, const QString &format) const
{
    return QStringLiteral("%1/json_%2.%3")
            .arg(qmOutputPath)
            .arg(locale)
            .arg(format)
    ;
}

QJsonDocument CTranslator::createDocument(const QString &jsonFilePath) const
{
    QFile file(jsonFilePath);
    QJsonDocument document;

    if (file.open(QIODevice::ReadOnly)) {
        QJsonParseError error;
        document = QJsonDocument::fromJson(file.readAll(), &error);

        if (error.error != QJsonParseError::NoError) {
            qDebug("%s: Error parsing the json file: %s", Q_FUNC_INFO, qPrintable(error.errorString()));
        }
    }
    else {
        qDebug("%s: Can't open json file", Q_FUNC_INFO);
    }

    return document;
}

bool CTranslator::saveDocument(const QJsonDocument &jsonDocument, const QString &jsonFilePath) const
{
    QFile file(jsonFilePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if (file.write(jsonDocument.toJson()) != -1) {
            return true;
        }
        else {
            qDebug("%s: Error saving the json file: %s", Q_FUNC_INFO, qPrintable(file.errorString()));
        }
    }
    else {
        qDebug("%s: Can't open json file", Q_FUNC_INFO);
    }

    return false;
}

Translator CTranslator::createTranslator(const QString &locale, const QString &filePath) const
{
    Translator translator;

    if (filePath.isEmpty()) {
        translator.setSourceLanguageCode(QLocale(QLocale::English, QLocale::AnyCountry).name());
        translator.setLanguageCode(QLocale(locale).name());
        translator.setLocationsType(Translator::NoLocations);
    }
    else {
        ConversionData cd;
        if (!translator.load(filePath, cd, "auto")) {
            qDebug("%s: Can't load translations: %s", Q_FUNC_INFO, qPrintable(filePath));
        }
    }

    return translator;
}

Translator &CTranslator::getTranslator(const QString &locale, const QString &filePath)
{
    const QString key = locale.trimmed().toLower();

    if (!m_translators.contains(key)) {
        m_translators[key] = createTranslator(locale, filePath);
    }

    return m_translators[key];
}

void CTranslator::insertTranslatorMessage(const QString &locale, const QString &context, const QString &source,
                                          const QString &translation)
{
    Q_ASSERT(!source.isEmpty());
    TranslatorMessage msg;
    msg.setContext(context);
    msg.setSourceText(source);
    msg.setTranslation(translation);
    msg.setType(translation.isEmpty() ? TranslatorMessage::Unfinished : TranslatorMessage::Finished);

    Translator &translator = getTranslator(locale);

    if (translator.find(msg) != -1) {
        qDebug("%s: Message already exists in '%s': %s/%s.",
               Q_FUNC_INFO, qPrintable(locale), qPrintable(context), qPrintable(source));
        return;
    }

    translator.append(msg);
}

void CTranslator::exportArrayObjects(const QJsonArray &jsonArray, const QString &top, const QString &child)
{
    // top
    for (int i = 0; i < jsonArray.count(); ++i) {
        const QStringList keys = SUPPORTED_LOCALES;
        const QJsonObject object = jsonArray.at(i).toObject();
        const QString sourceKey = object.value(QStringLiteral("name")).toString();
        if (sourceKey.isEmpty())
            continue;

        foreach (const QString &key, keys) {
            if (QLocale(key) != QLocale::c()) {
                insertTranslatorMessage(key, top, sourceKey, object.value(key).toString());
            }
        }

        // child
        if (!child.isEmpty() && object.contains(child)) {
            const QJsonArray childArray = object.value(child).toArray();
            exportArrayObjects(childArray, child);
        }
    }
}

void CTranslator::exportArrayOfObjects(const QJsonObject &jsonDocumentObject, const QString &top, const QString &child)
{
    exportArrayObjects(jsonDocumentObject.value(top).toArray(), top, child);
}

bool CTranslator::doExport(const QJsonDocument &jsonDocument, const QString &qmOutputPath)
{
    m_translators.clear();

    const QJsonObject jsonDocumentObject = jsonDocument.object();
    QJsonArray rootArray;
    rootArray.insert(0, jsonDocumentObject);

    // export translatable properties from json document
    exportArrayObjects(rootArray, "root");
    exportArrayOfObjects(jsonDocumentObject, QStringLiteral("extensions"));
    exportArrayOfObjects(jsonDocumentObject, QStringLiteral("units"));
    exportArrayOfObjects(jsonDocumentObject, QStringLiteral("variables"));
    exportArrayOfObjects(jsonDocumentObject, QStringLiteral("streams"), QStringLiteral("measures"));
    exportArrayOfObjects(jsonDocumentObject, QStringLiteral("actions"), QStringLiteral("steps"));
    exportArrayOfObjects(jsonDocumentObject, QStringLiteral("cycles"), QStringLiteral("steps"));

    // generate files
    foreach (const Translator &translator, m_translators.values()) {
        const QString filePath = translationsFilePath(qmOutputPath, translator.languageCode(), QStringLiteral("ts"));
        ConversionData cd;

        if (!translator.save(filePath, cd, "auto")) {
            qDebug("%s: Can't save translations ts file: %s", Q_FUNC_INFO, qPrintable(filePath));
        }
    }

    return true;
}

QString CTranslator::translatorMessage(const QString &locale, const QString &context, const QString &source)
{
    TranslatorMessage msg;
    msg.setContext(context);
    msg.setSourceText(source);

    Translator &translator = getTranslator(locale);
    const int index = translator.find(msg);

    if (index != -1) {
        const QString translation = translator.constMessage(index).translation();

        if (!translation.isEmpty()) {
            return translation;
        }
    }

    return QString();
}

void CTranslator::importArrayObjects(QJsonArray &jsonArray, const QString &top, const QString &child)
{
    // top
    for (int i = 0; i < jsonArray.count(); ++i) {
        const QStringList keys = SUPPORTED_LOCALES;
        QJsonObject object = jsonArray.at(i).toObject();
        const QString sourceKey = object.value(QStringLiteral("name")).toString();

        foreach (const QString &key, keys) {
            if (QLocale(key) != QLocale::c()) {
                const QString translation = translatorMessage(key, top, sourceKey);

                if (translation.isEmpty()) {
                    object.remove(key);
                }
                else {
                    object.insert(key, translation);
                }
            }
        }

        // child
        if (!child.isEmpty() && object.contains(child)) {
            QJsonArray childArray = object.value(child).toArray();
            importArrayObjects(childArray, child);
            object.insert(child, childArray);
        }

        jsonArray[i] = object;
    }
}

void CTranslator::importArrayOfObjects(QJsonObject &jsonDocumentObject, const QString &top, const QString &child)
{
    if (!top.isEmpty() && jsonDocumentObject.contains(top)) {
        QJsonArray jsonArray = jsonDocumentObject.value(top).toArray();
        importArrayObjects(jsonArray, top, child);
        jsonDocumentObject.insert(top, jsonArray);
    }
}

bool CTranslator::doImport(QJsonDocument &jsonDocument, const QString &qmOutputPath)
{
    m_translators.clear();

    // load translations
    foreach (const QString &locale, SUPPORTED_LOCALES) {
        const QString filePath = translationsFilePath(qmOutputPath, locale, QStringLiteral("ts"));
        getTranslator(locale, filePath);
    }

    QJsonObject jsonDocumentObject = jsonDocument.object();
    QJsonArray rootArray;
    rootArray.insert(0, jsonDocumentObject);

    // import translations into the json document
    importArrayObjects(rootArray, QStringLiteral("root"));
    jsonDocumentObject = rootArray[0].toObject();
    importArrayOfObjects(jsonDocumentObject, QStringLiteral("extensions"));
    importArrayOfObjects(jsonDocumentObject, QStringLiteral("units"));
    importArrayOfObjects(jsonDocumentObject, QStringLiteral("variables"));
    importArrayOfObjects(jsonDocumentObject, QStringLiteral("streams"), QStringLiteral("measures"));
    importArrayOfObjects(jsonDocumentObject, QStringLiteral("actions"), QStringLiteral("steps"));
    importArrayOfObjects(jsonDocumentObject, QStringLiteral("cycles"), QStringLiteral("steps"));
    jsonDocument = QJsonDocument(jsonDocumentObject);

    return true;
}

