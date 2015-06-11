#include "CUpdateDialog.h"
#include "ui_CUpdateDialog.h"
#include "CUpdateManager.h"

#include <CMessageBox.h>
#include <CPCWindow.h>
#include <QCloseEvent>

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
    CMessageBox *mb = CPCWindow::openModal<CMessageBox>(error);
    connect(mb, &QWidget::destroyed, this, &CUpdateDialog::reject);
}

void CUpdateDialog::slotFinished(bool success)
{
    if (success) {
        CMessageBox *mb = CPCWindow::openModal<CMessageBox>(tr("The update were done correctly.\nThe application will restart."));
        connect(mb, &QWidget::destroyed, this, &CUpdateDialog::accept);
    }
    else {
        CMessageBox *mb = CPCWindow::openModal<CMessageBox>(tr("The update process failed."));
        connect(mb, &QWidget::destroyed, this, &CUpdateDialog::reject);
    }
}
