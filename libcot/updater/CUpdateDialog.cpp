#include "CUpdateDialog.h"
#include "ui_CUpdateDialog.h"
#include "CUpdateManager.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QPushButton>

CUpdateDialog::CUpdateDialog(CUpdateManager *updateManager, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CUpdateDialog)
    , m_updateManager(updateManager)
{
    ui->setupUi(this);

    ui->lTitle->setText(tr("Update %1 is available, do you want to update now?").arg(updateManager->availableVersion()));

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered, this, &CUpdateDialog::slotPerformUpdate);
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered, this, &CUpdateDialog::reject);

    connect(m_updateManager, &CUpdateManager::signalError, this, &CUpdateDialog::slotError);
    connect(m_updateManager, &CUpdateManager::signalFinished, this, &CUpdateDialog::slotFinished);
}

CUpdateDialog::~CUpdateDialog()
{
    delete ui;
}

void CUpdateDialog::closeEvent(QCloseEvent *event)
{
    if (m_updateManager->isRunning()) {
        event->ignore();
        return;
    }

    QDialog::closeEvent(event);
}

void CUpdateDialog::slotPerformUpdate()
{
    ui->vbbButtons->action(CToolButton::Ok)->setEnabled(false);
    ui->vbbButtons->action(CToolButton::Cancel)->setEnabled(false);
    m_updateManager->slotUpdateSoftware();
}

void CUpdateDialog::slotError(const QString &error)
{
    QMessageBox::critical(this, QString(), error);
    reject();
}

void CUpdateDialog::slotFinished(bool success)
{
    if (success) {
        QMessageBox::information(this, QString(), tr("The update were done correctly.\nThe application will restart."));
        accept();
    }
    else {
        QMessageBox::critical(this, QString(), tr("The update process fails."));
        reject();
    }
}
