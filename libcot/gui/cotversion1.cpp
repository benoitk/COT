#include "cotversion1.h"
#include "ui_cotversion1.h"
#include "CUpdateManager.h"
#include "CUpdateDialog.h"

COTVersion1::COTVersion1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::COTVersion1)
    , m_updateManager(new CUpdateManager(this))
{
    m_updateManager->init();

    ui->setupUi(this);
    ui->tbUpdate->setVisible(false);

    connect(m_updateManager, &CUpdateManager::signalUpdateAvailable, this, &COTVersion1::slotUpdateAvailable);
    connect(ui->tbUpdate, &QToolButton::clicked, this, &COTVersion1::slotUpdateClicked);
}

COTVersion1::~COTVersion1()
{
    delete ui;
}

void COTVersion1::slotUpdateAvailable(const QString &version)
{
    ui->tbUpdate->setToolTip(tr("Upgrade to version %1").arg(version));

    if (qApp->applicationVersion() > version) {
        ui->tbUpdate->setVisible(false);
    }
    else {
        ui->tbUpdate->setVisible(true);

        if (canShowUpdatePopup()) {
            if (CUpdateDialog::requestUserUpdate(version)) {
                ui->tbUpdate->click();
            }
        }
    }
}

bool COTVersion1::canShowUpdatePopup() const
{
    // TODO: check running cycles etc
    return !QApplication::activeModalWidget();
}

void COTVersion1::slotUpdateClicked()
{
    const QString appFilePath = qApp->applicationFilePath();
    CUpdateDialog dlg(m_updateManager, this);

    if (dlg.exec() == QDialog::Accepted) {
        if (QProcess::startDetached(appFilePath)) {
            close();
        }
    }

}
