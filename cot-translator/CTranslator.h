#ifndef CTRANSLATOR_H
#define CTRANSLATOR_H

#include <QObject>
#include <QJsonDocument>
#include <QHash>

#include "3rdparty/translator.h"

class CTranslator : public QObject
{
    Q_OBJECT

public:
    explicit CTranslator(QObject *parent = Q_NULLPTR);

    bool exportFrom(const QJsonDocument &jsonDocument, const QString &qmOutputPath);
    bool exportFrom(const QString &jsonFilePath, const QString &qmOutputPath);

    bool importFrom(const QString &qmOutputPath, QJsonDocument &jsonDocument);
    bool importFrom(const QString &qmOutputPath, const QString &jsonFilePath);

private:
    QHash<QString, Translator> m_translators;

    QString translationsFilePath(const QString &qmOutputPath, const QString &locale, const QString &format) const;
    QJsonDocument createDocument(const QString &jsonFilePath) const;
    bool saveDocument(const QJsonDocument &jsonDocument, const QString &jsonFilePath) const;
    Translator createTranslator(const QString &locale, const QString &filePath = QString()) const;
    Translator &getTranslator(const QString &locale, const QString &filePath = QString());

    void insertTranslatorMessage(const QString &locale, const QString &context, const QString &source,
                                 const QString &translation);
    void exportArrayObjects(const QJsonArray &jsonArray, const QString &top, const QString &child = QString());
    void exportArrayOfObjects(const QJsonObject &jsonDocumentObject, const QString &top, const QString &child = QString());
    bool doExport(const QJsonDocument &jsonDocument, const QString &qmOutputPath);

    QString translatorMessage(const QString &locale, const QString &context, const QString &source);
    void importArrayObjects(QJsonArray &jsonArray, const QString &top, const QString &child = QString());
    void importArrayOfObjects(QJsonObject &jsonDocumentObject, const QString &top, const QString &child = QString());
    bool doImport(QJsonDocument &jsonDocument, const QString &qmOutputPath);
};

#endif // CTRANSLATOR_H
