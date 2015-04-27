#include "CPCToolsTab.h"
#include "ui_CPCToolsTab.h"
#include "CLabelledToolButton.h"
#include "CPCWindow.h"
#include "CMaintenanceWindow.h"
#include "CElectricalTestsWindow.h"
#include "COptionsWindow.h"
#include "CHistoryWindow.h"
#include "CLogFilesWindow.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

#include <QGridLayout>
#include <QTextDocument>
#include <QTextOption>
#include <QTextBlock>
#include <QTextCursor>

CPCToolsTab::CPCToolsTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCToolsTab)
    , m_history(new QTextDocument(this))
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    QList<CLabelledToolButton *> buttons;
    buttons << new CLabelledToolButton(CToolButton::Maintenance, this);
    buttons << new CLabelledToolButton(CToolButton::ElectricalTests, this);
    buttons << new CLabelledToolButton(CToolButton::Options, this);
    buttons << new CLabelledToolButton(CToolButton::History, this);
    buttons << new CLabelledToolButton(CToolButton::LogFiles, this);

    const int layoutWidth = 2;
    QWidget *widget = new QWidget(this);
    QGridLayout *gl = new QGridLayout(widget);
    int x = 0;
    int y = 0;

    gl->setMargin(0);

    foreach (CLabelledToolButton *button, buttons) {
        m_buttons[button->type()] = button;
        gl->addWidget(button, y, x, Qt::AlignCenter);
        connect(button, &CLabelledToolButton::clicked, this, &CPCToolsTab::slotButtonClicked);

        x++;
        if (x == layoutWidth) {
            x = 0;
            y++;
        }
    }

    ui->swCentral->setScrollableWidget(widget);
    slotInitializeHistoryDocument();
    retranslate();

    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged, this, &CPCToolsTab::slotVariableChanged);
}

CPCToolsTab::~CPCToolsTab()
{
    delete ui;
}

void CPCToolsTab::retranslate()
{
    m_buttons[CToolButton::Maintenance]->setText(tr("Maintenance"));
    m_buttons[CToolButton::ElectricalTests]->setText(tr("Electrical test"));
    m_buttons[CToolButton::Options]->setText(tr("Options"));
    m_buttons[CToolButton::History]->setText(tr("History"));
    m_buttons[CToolButton::LogFiles]->setText(tr("Log files copy"));
}

void CPCToolsTab::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    IPCTab::changeEvent(event);
}

void CPCToolsTab::slotButtonClicked()
{
    CLabelledToolButton *button = qobject_cast<CLabelledToolButton *>(sender());

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
