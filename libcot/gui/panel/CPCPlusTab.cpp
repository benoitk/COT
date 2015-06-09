#include "CPCPlusTab.h"
#include "ui_CPCPlusTab.h"
#include "CLabelledToolButtonGrid.h"
#include "CLabelledToolButton.h"
#include "CPCWindow.h"
#include "CAboutWindow.h"
#include "CMessageBox.h"
#include "CConfigurationBackup.h"

CPCPlusTab::CPCPlusTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCPlusTab)
    , m_buttons(new CLabelledToolButtonGrid(2, this))
{
    m_buttons->setButtons(QList<CToolButton::Type>()
                          << CToolButton::Informations
                          << CToolButton::CreateRecovery
                          << CToolButton::RestoreConfig);

    ui->setupUi(this);
    ui->swCentral->setScrollablePagerWidget(m_buttons);
    // NOTE: we expect this view to never need scrolling
    //       if it gets extended in the future, uncomment the following two lines
//     ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
//     ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

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
        CPCWindow::openExec<CAboutWindow>();
        break;

    case CToolButton::CreateRecovery: {
        CConfigurationBackup bckp;
        const bool success = bckp.createRecoveryFile();
        if (success) {
            CPCWindow::openModal<CMessageBox>(tr("Backup file successfully created."));
        } else {
            CPCWindow::openModal<CMessageBox>(tr("ERROR: The backup file couldn't be created."));
        }
        break;
    }

    case CToolButton::RestoreConfig: {
        QString backupFile;
        CConfigurationBackup bckp;
        const bool success = bckp.overwriteConfigurationFile(&backupFile);
        if (success) {
            CPCWindow::openModal<CMessageBox>(tr("Configuration file successfully overwritten.\nThe previous configuration file was saved under the name:\n%1").arg(backupFile));
        } else {
            CPCWindow::openModal<CMessageBox>(tr("ERROR: The configuration file couldn't be overwritten."));
        }
        break;
    }

    default:
        Q_ASSERT(false);
        break;
    }
}
