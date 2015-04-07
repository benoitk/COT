#include "CTranslationGenerator.h"

#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>

CTranslationGenerator::CTranslationGenerator(QObject *parent)
    : QObject(parent)
{

}

CTranslationGenerator::~CTranslationGenerator()
{

}

bool CTranslationGenerator::generateFrom(const QJsonDocument &jsonDocument, const QString &qmOutputPath)
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

    return doScan(jsonDocument, qmOutputPath);
}

bool CTranslationGenerator::generateFrom(const QString &jsonFilePath, const QString &qmOutputPath)
{
    if (!QFile::exists(jsonFilePath)) {
        qDebug("%s: The json file does not exists: %s", Q_FUNC_INFO, qPrintable(jsonFilePath));
        return false;
    }

    return generateFrom(createDocument(jsonFilePath), qmOutputPath);
}

QJsonDocument CTranslationGenerator::createDocument(const QString &jsonFilePath) const
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

Translator CTranslationGenerator::createTranslator(const QString &locale) const
{
    Translator translator;
    translator.setSourceLanguageCode(QLocale(QLocale::English, QLocale::AnyCountry).name());
    translator.setLanguageCode(QLocale(locale).name());
    translator.setLocationsType(Translator::NoLocations);
    return translator;
}

Translator &CTranslationGenerator::getTranslator(const QString &locale)
{
    const QString key = locale.trimmed().toLower();

    if (!m_translators.contains(key)) {
        m_translators[key] = createTranslator(locale);
    }

    return m_translators[key];
}

void CTranslationGenerator::insertTranslatorMessage(const QString &locale, const TranslatorMessage &message)
{
    Translator &translator = getTranslator(locale);

    if (translator.find(message) != -1) {
        qDebug("%s: An entry for the exact same context/source text already exists.", Q_FUNC_INFO);
        return;
    }

    translator.append(message);
}

bool CTranslationGenerator::doScan(const QJsonDocument &jsonDocument, const QString &qmOutputPath)
{
    /* Memo of translatable properties
     * - root (name) - json object
     * - extensions (name) - json array of objects
     * - units (name) - json array of objects
     * - variables (name) - json array of objects
     * - streams (name) - json array of objects
     *  - measures (name) - json array of objects
     * - actions (name) - json array of objects
     *  - steps - json array of objects
     * - cycles (name) - json array of objects
     *  - steps - json array of objects
     * Streams, Measures and Steps do normally not have names, but as it's needed for translations
     * we will argue, names are auto generated for those classes and that the technician don't care about them.
    */

    // root
    {
        const QJsonObject root = jsonDocument.object();
        const QStringList keys = root.keys();
        const QString sourceKey = root.value("name").toString();

        foreach (const QString &key, keys) {
            // We assume locale to be complete
            if (!key.contains("_")) {
                continue;
            }

            if (QLocale(key) != QLocale::c()) {
                TranslatorMessage msg;
                msg.setContext("root");
                msg.setSourceText(sourceKey);
                msg.setTranslation(root.value(key).toString());
                msg.setType(TranslatorMessage::Finished);
                insertTranslatorMessage(key, msg);
            }
        }
    }

    // extensions
    {
        const QJsonArray extensions = jsonDocument.object().value("extensions").toArray();

        for (int i = 0; i < extensions.count(); i++) {
            const QJsonObject extension = extensions.at(i).toObject();
            const QStringList keys = extension.keys();
            const QString sourceKey = extension.value("name").toString();

            foreach (const QString &key, keys) {
                // We assume locale to be complete
                if (!key.contains("_")) {
                    continue;
                }

                if (QLocale(key) != QLocale::c()) {
                    TranslatorMessage msg;
                    msg.setContext("extensions");
                    msg.setSourceText(sourceKey);
                    msg.setTranslation(extension.value(key).toString());
                    msg.setType(TranslatorMessage::Finished);
                    insertTranslatorMessage(key, msg);
                }
            }
        }
    }

    // units
    {
        const QJsonArray units = jsonDocument.object().value("units").toArray();

        for (int i = 0; i < units.count(); i++) {
            const QJsonObject unit = units.at(i).toObject();
            const QStringList keys = unit.keys();
            const QString sourceKey = unit.value("name").toString();

            foreach (const QString &key, keys) {
                // We assume locale to be complete
                if (!key.contains("_")) {
                    continue;
                }

                if (QLocale(key) != QLocale::c()) {
                    TranslatorMessage msg;
                    msg.setContext("units");
                    msg.setSourceText(sourceKey);
                    msg.setTranslation(unit.value(key).toString());
                    msg.setType(TranslatorMessage::Finished);
                    insertTranslatorMessage(key, msg);
                }
            }
        }
    }

    // variables
    {
        const QJsonArray variables = jsonDocument.object().value("variables").toArray();

        for (int i = 0; i < variables.count(); i++) {
            const QJsonObject variable = variables.at(i).toObject();
            const QStringList keys = variable.keys();
            const QString sourceKey = variable.value("name").toString();

            foreach (const QString &key, keys) {
                // We assume locale to be complete
                if (!key.contains("_")) {
                    continue;
                }

                if (QLocale(key) != QLocale::c()) {
                    TranslatorMessage msg;
                    msg.setContext("variables");
                    msg.setSourceText(sourceKey);
                    msg.setTranslation(variable.value(key).toString());
                    msg.setType(TranslatorMessage::Finished);
                    insertTranslatorMessage(key, msg);
                }
            }
        }
    }

    // streams
    {
        const QJsonArray streams = jsonDocument.object().value("streams").toArray();

        for (int i = 0; i < streams.count(); i++) {
            const QJsonObject stream = streams.at(i).toObject();
            const QStringList keys = stream.keys();
            const QString sourceKey = stream.value("name").toString();

            foreach (const QString &key, keys) {
                // We assume locale to be complete
                if (!key.contains("_")) {
                    continue;
                }

                if (QLocale(key) != QLocale::c()) {
                    TranslatorMessage msg;
                    msg.setContext("streams");
                    msg.setSourceText(sourceKey);
                    msg.setTranslation(stream.value(key).toString());
                    msg.setType(TranslatorMessage::Finished);
                    insertTranslatorMessage(key, msg);
                }
            }

            // measures
            {
                const QJsonArray measures = jsonDocument.object().value("measures").toArray();

                for (int i = 0; i < measures.count(); i++) {
                    const QJsonObject measure = measures.at(i).toObject();
                    const QStringList measureKeys = measure.keys();
                    const QString measureSourceKey = measure.value("name").toString();

                    foreach (const QString &measureKey, measureKeys) {
                        // We assume locale to be complete
                        if (!measureKey.contains("_")) {
                            continue;
                        }

                        if (QLocale(measureKey) != QLocale::c()) {
                            TranslatorMessage msg;
                            msg.setContext("measures");
                            msg.setSourceText(measureSourceKey);
                            msg.setTranslation(measure.value(measureKey).toString());
                            msg.setType(TranslatorMessage::Finished);
                            insertTranslatorMessage(measureKey, msg);
                        }
                    }
                }
            }
        }
    }

    // actions
    {
        const QJsonArray actions = jsonDocument.object().value("actions").toArray();

        for (int i = 0; i < actions.count(); i++) {
            const QJsonObject action = actions.at(i).toObject();
            const QStringList keys = action.keys();
            const QString sourceKey = action.value("name").toString();

            foreach (const QString &key, keys) {
                // We assume locale to be complete
                if (!key.contains("_")) {
                    continue;
                }

                if (QLocale(key) != QLocale::c()) {
                    TranslatorMessage msg;
                    msg.setContext("actions");
                    msg.setSourceText(sourceKey);
                    msg.setTranslation(action.value(key).toString());
                    msg.setType(TranslatorMessage::Finished);
                    insertTranslatorMessage(key, msg);
                }
            }

            // steps
            {
                const QJsonArray steps = jsonDocument.object().value("steps").toArray();

                for (int i = 0; i < steps.count(); i++) {
                    const QJsonObject step = steps.at(i).toObject();
                    const QStringList stepKeys = step.keys();
                    const QString stepSourceKey = step.value("name").toString();

                    foreach (const QString &stepKey, stepKeys) {
                        // We assume locale to be complete
                        if (!stepKey.contains("_")) {
                            continue;
                        }

                        if (QLocale(stepKey) != QLocale::c()) {
                            TranslatorMessage msg;
                            msg.setContext("steps");
                            msg.setSourceText(stepSourceKey);
                            msg.setTranslation(step.value(stepKey).toString());
                            msg.setType(TranslatorMessage::Finished);
                            insertTranslatorMessage(stepKey, msg);
                        }
                    }
                }
            }
        }
    }

    // cycles
    {
        const QJsonArray cycles = jsonDocument.object().value("cycles").toArray();

        for (int i = 0; i < cycles.count(); i++) {
            const QJsonObject cycle = cycles.at(i).toObject();
            const QStringList keys = cycle.keys();
            const QString sourceKey = cycle.value("name").toString();

            foreach (const QString &key, keys) {
                // We assume locale to be complete
                if (!key.contains("_")) {
                    continue;
                }

                if (QLocale(key) != QLocale::c()) {
                    TranslatorMessage msg;
                    msg.setContext("cycles");
                    msg.setSourceText(sourceKey);
                    msg.setTranslation(cycle.value(key).toString());
                    msg.setType(TranslatorMessage::Finished);
                    insertTranslatorMessage(key, msg);
                }
            }

            // steps
            {
                const QJsonArray steps = jsonDocument.object().value("steps").toArray();

                for (int i = 0; i < steps.count(); i++) {
                    const QJsonObject step = steps.at(i).toObject();
                    const QStringList stepKeys = step.keys();
                    const QString stepSourceKey = step.value("name").toString();

                    foreach (const QString &stepKey, stepKeys) {
                        // We assume locale to be complete
                        if (!stepKey.contains("_")) {
                            continue;
                        }

                        if (QLocale(stepKey) != QLocale::c()) {
                            TranslatorMessage msg;
                            msg.setContext("steps");
                            msg.setSourceText(stepSourceKey);
                            msg.setTranslation(step.value(stepKey).toString());
                            msg.setType(TranslatorMessage::Finished);
                            insertTranslatorMessage(stepKey, msg);
                        }
                    }
                }
            }
        }
    }

    // generate files
    foreach (const Translator &translator, m_translators.values()) {
        QLocale::Language language;
        QLocale::Country country;
        translator.languageAndCountry(translator.languageCode(), &language, &country);

        const QString filePath = QString("%1/json_%2.qm").arg(qmOutputPath).arg(QLocale(language, country).name());
        ConversionData cd;

        if (!translator.save(filePath, cd, "auto")) {
            qDebug("%s: Can't save translations file: %s", Q_FUNC_INFO, qPrintable(filePath));
        }
    }

    return true;
}

