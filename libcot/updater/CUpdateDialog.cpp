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
    ui->dbbButtons->button(QDialogButtonBox::Apply)->setText(tr("Update"));

    connect(ui->dbbButtons, &QDialogButtonBox::clicked, this, &CUpdateDialog::slotButtonClicked);
    connect(m_updateManager, &CUpdateManager::signalError, this, &CUpdateDialog::slotError);
    connect(m_updateManager, &CUpdateManager::signalFinished, this, &CUpdateDialog::slotFinished);
}

CUpdateDialog::~CUpdateDialog()
{
    delete ui;
}

bool CUpdateDialog::requestUserUpdate(const QString &version)
{
    return QMessageBox::question(0, QString(), tr("Update %1 is available, do you want to update now ?").arg(version),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes;
}

void CUpdateDialog::closeEvent(QCloseEvent *event)
{
    if (m_updateManager->isRunning()) {
        event->ignore();
        return;
    }

    QDialog::closeEvent(event);
}

void CUpdateDialog::slotButtonClicked(QAbstractButton *button)
{
    const QDialogButtonBox::StandardButton standardButton = ui->dbbButtons->standardButton(button);

    switch (standardButton) {
    case QDialogButtonBox::Apply: {
        ui->dbbButtons->button(QDialogButtonBox::Apply)->setEnabled(false);
        ui->dbbButtons->button(QDialogButtonBox::Cancel)->setEnabled(false);
        m_updateManager->slotUpdateSoftware();
        break;
    }

    case QDialogButtonBox::Cancel: {
        reject();
        break;
    }

    default:
        break;
    }
}

void CUpdateDialog::slotError(const QString &error)
{
    QMessageBox::critical(this, QString(), error);
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
