#include "CPCToolsTab.h"
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

#include <QTextDocument>
#include <QTextOption>
#include <QTextBlock>
#include <QTextCursor>

CPCToolsTab::CPCToolsTab(QWidget *parent)
    : IPCTab(parent)
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

    ui->setupUi(this);
    ui->swCentral->setScrollableWidget(m_buttons);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    slotInitializeHistoryDocument();
    retranslate();

    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged, this, &CPCToolsTab::slotVariableChanged);
    connect(m_buttons, &CLabelledToolButtonGrid::clicked, this, &CPCToolsTab::slotButtonClicked);
}

CPCToolsTab::~CPCToolsTab()
{
    delete ui;
}

void CPCToolsTab::retranslate()
{
    m_buttons->button(CToolButton::Maintenance)->setText(tr("Maintenance"));
    m_buttons->button(CToolButton::ElectricalTests)->setText(tr("Electrical test"));
    m_buttons->button(CToolButton::Options)->setText(tr("Options"));
    m_buttons->button(CToolButton::History)->setText(tr("History"));
    m_buttons->button(CToolButton::LogFiles)->setText(tr("Log files copy"));
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
    switch (button->type()) {
        case CToolButton::Maintenance:
            CPCWindow::openModal<CMaintenanceWindow>();
            break;

        case CToolButton::ElectricalTests:
            CPCWindow::openModal<CElectricalTestsWindow>();
            break;

        case CToolButton::Options:
            CPCWindow::openModal<COptionsWindow>();
            break;

        case CToolButton::History:
            CPCWindow::openModal<CHistoryWindow>(m_history);
            break;

        case CToolButton::LogFiles:
            CPCWindow::openModal<CLogFilesWindow>();
            break;

        default:
            Q_ASSERT(false);
            break;
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
    m_history->setMaximumBlockCount(50000); // KDAB_TODO: Need customer api to read this feature
    // KDAB_TODO: Call clear on an interval defined by the user - need customer api
}

void CPCToolsTab::slotVariableChanged(const QString &name, const QDateTime &dateTime)
{
    CAutomate *automate = CAutomate::getInstance();
    IVariable *ivar = automate->getVariable(name);

    if (!automate->getDisplayConf()->getListForScreenHistory().contains(ivar)) {
        return;
    }

    const QString text = CAutomate::getInstance()->formatHistoryEntry(name, dateTime);
    QTextCursor cursor(m_history);

    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText(text);
}
