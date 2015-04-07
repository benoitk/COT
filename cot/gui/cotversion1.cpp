#include "cotversion1.h"
#include "ui_cotversion1.h"
#include "CTranslator.h"

COTVersion1::COTVersion1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::COTVersion1)
{
    ui->setupUi(this);

    connect(ui->actionExport, &QAction::triggered, this, &COTVersion1::slotExportTranslations);
    connect(ui->actionImport, &QAction::triggered, this, &COTVersion1::slotImportTranslations);
}

COTVersion1::~COTVersion1()
{
    delete ui;
}

void COTVersion1::slotExportTranslations()
{
    const QString jsonFile = jsonFilePath();
    const QString output = translationsPath();
    CTranslator translator;

    if (!translator.exportFrom(jsonFile, output)) {
        qDebug("%s: Can't export translations (%s).", Q_FUNC_INFO, qPrintable(output));
    }
}

void COTVersion1::slotImportTranslations()
{
    const QString jsonFile = jsonFilePath();
    const QString output = translationsPath();
    CTranslator translator;

    if (!translator.importFrom(output, jsonFile)) {
        qDebug("%s: Can't import translations (%s).", Q_FUNC_INFO, qPrintable(output));
    }
}

QString COTVersion1::jsonFilePath() const
{
    return QString::fromUtf8(COT_JSON_FILE);
}

QString COTVersion1::translationsPath() const
{
    return QStringLiteral("%1/%2translations/")
            .arg(QApplication::applicationDirPath())
            .arg(
            #if defined(Q_OS_MACX)
                QStringLiteral("/../Resources/")
            #else
                QString()
            #endif
                )
            ;
}
