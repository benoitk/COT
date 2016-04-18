#include "CPCPlusTab.h"
#include "ui_CPCPlusTab.h"
#include "CLabelledToolButtonGrid.h"
#include "CLabelledToolButton.h"
#include "CPCWindow.h"
#include "CAboutWindow.h"
#include "CMessageBox.h"
#include "CConfigurationBackup.h"
#include "tools/screenshot/CDialogScreenShots.h"

#include <QProcess>

CPCPlusTab::CPCPlusTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCPlusTab)
    , m_buttons(new CLabelledToolButtonGrid(2, this))
{
    m_buttons->setButtons(QList<CToolButton::Type>()
                          << CToolButton::Informations
                          << CToolButton::CreateRecovery
                 //         << CToolButton::Screenshot
                          << CToolButton::RestoreConfig);

    ui->setupUi(this);
    ui->swCentral->setScrollablePagerWidget(m_buttons);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    retranslate();

    connect(m_buttons, &CLabelledToolButtonGrid::clicked, this, &CPCPlusTab::slotButtonClicked);
}

CPCPlusTab::~CPCPlusTab()
{
    delete ui;
}

CVerticalButtonBar *CPCPlusTab::buttonBar() const
{
    return ui->vbbButtons;
}

void CPCPlusTab::retranslate()
{
    m_buttons->button(CToolButton::Informations)->setText(tr("Informations"));
    m_buttons->button(CToolButton::CreateRecovery)->setText(tr("Create recovery file"));
    m_buttons->button(CToolButton::RestoreConfig)->setText(tr("Recover configuration file"));
}

void CPCPlusTab::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    IPCTab::changeEvent(event);
}

void CPCPlusTab::slotButtonClicked(CLabelledToolButton *button)
{

    switch (button->type()) {
    case CToolButton::Informations:
        CPCWindow::openExec<CAboutWindow>(this);
        break;

    case CToolButton::CreateRecovery: {
        if(CUserSession::getInstance()->loginAdmin()){
            CConfigurationBackup bckp;
            const QString error = bckp.createRecoveryFile();
            if (error.isEmpty()) {
                CPCWindow::openModal<CMessageBox>(tr("Backup file successfully created."));
            } else {
                CPCWindow::openModal<CMessageBox>(tr("ERROR: The backup file couldn't be created.\n%1").arg(error));
            }
        }
        break;
    }

    case CToolButton::RestoreConfig: {
        if(CUserSession::getInstance()->loginAdmin()){
            QString backupFile;
            CConfigurationBackup bckp;
            const QString error = bckp.overwriteConfigurationFile(&backupFile);
            //en attendant de mettre une vrai boite de dialog avec barre de défilement pour être sur que la copie soit finit ...
#ifdef   Q_OS_UNIX
    QProcess process;
    process.start("sync");
    process.waitForFinished();
#endif

            //TODO : remplacer la message box par une boite de copie de fichier, avec barre de défillement
            if (error.isEmpty()) {
                CPCWindow::openModal<CMessageBox>(tr("Configuration file successfully overwritten.\nThe previous configuration file was saved under the name:\n%1").arg(backupFile));
            } else {
                CPCWindow::openModal<CMessageBox>(tr("ERROR: The configuration file couldn't be overwritten.\n%1").arg(error));
            }
        }
        break;
    }
    case CToolButton::Screenshot:{
        if(CUserSession::getInstance()->loginAdmin())
            CDialogScreenShots::getInstance()->exec();
    }
        break;
    default:
        Q_ASSERT(false);
        break;
    }
}
