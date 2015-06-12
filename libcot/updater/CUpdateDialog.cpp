#include "CUpdateDialog.h"
#include "ui_CUpdateDialog.h"
#include "CUpdateManager.h"

#include <CMessageBox.h>
#include <CPCWindow.h>
#include <QCloseEvent>

CUpdateDialog::CUpdateDialog(CUpdateManager *updateManager, QWidget *parent)
    : CDialog(parent)
    , ui(new Ui::CUpdateDialog)
    , m_updateManager(updateManager)
{
    setTitle(tr("UPDATE"));
    QWidget *main = new QWidget(this);
    ui->setupUi(main);
    setMainWidget(main);

    ui->lTitle->setText(ui->lTitle->text().arg(updateManager->availableVersion()));
    ui->lTitle->setMinimumWidth(300);

    connect(buttonBar()->addAction(CToolButton::Ok), &QAction::triggered, this, &CUpdateDialog::slotPerformUpdate);
    connect(buttonBar()->addAction(CToolButton::Cancel), &QAction::triggered, this, &CUpdateDialog::reject);

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
    buttonBar()->action(CToolButton::Ok)->setEnabled(false);
    buttonBar()->action(CToolButton::Cancel)->setEnabled(false);
    m_updateManager->slotUpdateSoftware();
}

void CUpdateDialog::slotError(const QString &error)
{
    CPCWindow::openExec<CMessageBox>(error);
    reject();
}

void CUpdateDialog::slotFinished(bool success)
{
    if (success) {
        CPCWindow::openExec<CMessageBox>(tr("The update were done correctly.\nThe application will restart."));
        accept();
    }
    else {
        CPCWindow::openExec<CMessageBox>(tr("The update process failed."));
        reject();
    }
}
