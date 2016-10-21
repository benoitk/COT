#include "CPCToolsTab.h"
#include "CDialogConfirmation.h"
#include "ui_CPCToolsTab.h"
#include "CLabelledToolButtonGrid.h"
#include "CLabelledToolButton.h"
#include "CPCWindow.h"
#include "CMaintenanceWindow.h"
#include "CElectricalTestsWindow.h"
#include "COptionsWindow.h"
#include "CHistoryWindow.h"
#include "CLogFilesWindow.h"
#include "CAutomate.h"
#include "CDisplayConf.h"
#include "CConfiguratorWindow.h"


#include <QTextDocument>
#include <QTextOption>
#include <QTextBlock>
#include <QTextCursor>

CPCToolsTab::CPCToolsTab(CAutomate* arg_automate, QWidget *parent)
    : IPCTab(arg_automate, parent)
    , ui(new Ui::CPCToolsTab)
    , m_buttons(new CLabelledToolButtonGrid(2, this))
    , m_history(new QTextDocument(this))
{
    m_buttons->setButtons(QList<CToolButton::Type>()
                          << CToolButton::Maintenance
                          << CToolButton::ElectricalTests
                          << CToolButton::Options
                          << CToolButton::History
                          << CToolButton::LogFiles);
                       //   << CToolButton::Configure);

    ui->setupUi(this);
    ui->swCentral->setScrollablePagerWidget(m_buttons);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    slotInitializeHistoryDocument();
    retranslate();

    connect(m_automate, &CAutomate::signalVariableChanged, this, &CPCToolsTab::slotVariableChanged);
    connect(m_buttons, &CLabelledToolButtonGrid::clicked, this, &CPCToolsTab::slotButtonClicked);
}

CPCToolsTab::~CPCToolsTab()
{
    delete ui;
}

CVerticalButtonBar *CPCToolsTab::buttonBar() const
{
    return ui->vbbButtons;
}

void CPCToolsTab::retranslate()
{
    m_buttons->button(CToolButton::Maintenance)->setText(tr("Maintenance"));
    m_buttons->button(CToolButton::ElectricalTests)->setText(tr("Electrical test"));
    m_buttons->button(CToolButton::Options)->setText(tr("Options"));
    m_buttons->button(CToolButton::History)->setText(tr("History"));
    m_buttons->button(CToolButton::LogFiles)->setText(tr("Log files copy"));
//    m_buttons->button(CToolButton::Configure)->setText(tr("Configurator"));
}

void CPCToolsTab::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    IPCTab::changeEvent(event);
}

void CPCToolsTab::slotButtonClicked(CLabelledToolButton *button)
{
    if(CUserSession::getInstance()->loginUser()){
        switch (button->type()) {
        case CToolButton::Maintenance:
            if((m_automate->isCyclesRunning() && CPCWindow::openExec<CDialogConfirmation>(tr("Are you sure ? \nIt will stop the current measurment"),this))
                    || !m_automate->isCyclesRunning()){
                m_automate->enterMaintenanceMode();
                CPCWindow::openModal<CMaintenanceWindow>(m_automate);
//                connect(CUserSession::getInstance(), &CUserSession::signalUserSessionClosed,
//                              CMaintenanceWindow::getInstance(), &CMaintenanceWindow::slotUserSessionClosed);
                //CPCWindow::openModal(CMaintenanceWindow::getInstance(), false);
//            }else if(!m_automate->isCyclesRunning()){
//                m_automate->enterMaintenanceMode();
//                //CPCWindow::openModal<CMaintenanceWindow>();
//                connect(CUserSession::getInstance(), &CUserSession::signalUserSessionClosed,
//                              CMaintenanceWindow::getInstance(), &CMaintenanceWindow::slotUserSessionClosed);
//                CPCWindow::openModal(CMaintenanceWindow::getInstance(), false);
            }
            break;

        case CToolButton::ElectricalTests:
            CPCWindow::openModal<CElectricalTestsWindow>(m_automate);
            break;

        case CToolButton::Options:
            CPCWindow::openModal<COptionsWindow>(m_automate);
            break;

        case CToolButton::History:
            CPCWindow::openModal<CHistoryWindow>(m_automate, m_history);
            break;

        case CToolButton::LogFiles:
            CPCWindow::openExec<CLogFilesWindow>(this);
            break;
        case CToolButton::Configure:
            CPCWindow::openModal<CConfiguratorWindow>(m_automate);
            break;
        default:
            Q_ASSERT(false);
            break;
        }
    }
}

void CPCToolsTab::slotInitializeHistoryDocument()
{
    QPlainTextDocumentLayout *layout = new QPlainTextDocumentLayout(m_history);
    m_history->setDocumentLayout(layout);

    QTextOption option = m_history->defaultTextOption();
    option.setTabStop(40);
    m_history->setDefaultTextOption(option);

    m_history->setUndoRedoEnabled(false);
    // remove old lines once we reach 150 lines (approx 5 screens)
    m_history->setMaximumBlockCount(150);
}

// This is done here rather than in CHistoryWindow, so that the history document stores all
// changes, even when the window isn't visible (created).
void CPCToolsTab::slotVariableChanged(const QString &name, const QDateTime &dateTime)
{
    CAutomate *automate = m_automate;
    IVariable *ivar = automate->getVariable(name);

    if (!automate->getDisplayConf()->getListForScreenHistory().contains(ivar)) {
        return;
    }

    const QString text = m_automate->formatHistoryEntry(name, dateTime);
    QTextCursor cursor(m_history);

    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText(text);
}
