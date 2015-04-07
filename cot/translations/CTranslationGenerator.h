#ifndef CTRANSLATIONGENERATOR_H
#define CTRANSLATIONGENERATOR_H

#include <QObject>
#include <QJsonDocument>
#include <QHash>

#include "3rdparty/translator.h"

class CTranslationGenerator : public QObject
{
    Q_OBJECT

public:
    explicit CTranslationGenerator(QObject *parent = 0);
    ~CTranslationGenerator();

    bool generateFrom(const QJsonDocument &jsonDocument, const QString &qmOutputPath);
    bool generateFrom(const QString &jsonFilePath, const QString &qmOutputPath);

private:
    QHash<QString, Translator> m_translators;

    QJsonDocument createDocument(const QString &jsonFilePath) const;
    Translator createTranslator(const QString &locale) const;

    Translator &getTranslator(const QString &locale);
    void insertTranslatorMessage(const QString &locale, const TranslatorMessage &message);
    bool doScan(const QJsonDocument &jsonDocument, const QString &qmOutputPath);
};

#endif // CTRANSLATIONGENERATOR_H
