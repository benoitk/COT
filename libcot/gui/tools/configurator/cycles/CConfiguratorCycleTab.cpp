#include "CConfiguratorCycleTab.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"
#include "CConfiguratorCycleTabUIHandler.h"
#include "CEditCycleWindow.h"
#include "CPCWindow.h"

#include <CAutomate.h>
#include <CVariableFactory.h>
#include <CVariableStream.h>
#include <CCycleFactory.h>

CConfiguratorCycleTab::CConfiguratorCycleTab(CAutomate* arg_automate, QWidget *parent)
    : IConfiguratorTab(parent)
    , m_handler(new CConfiguratorCycleTabUIHandler(arg_automate, scrollableWidget(), this))
    , m_automate(arg_automate)
{
    slotUpdateLayout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorCycleTab::slotAddCycle);
    connect(arg_automate, &CAutomate::signalStreamsUpdated, this, &CConfiguratorCycleTab::slotUpdateLayout);
    connect(arg_automate, &CAutomate::signalCyclesUpdated, this, &CConfiguratorCycleTab::slotUpdateLayout);
    initBaseTab();
}

void CConfiguratorCycleTab::slotAddCycle()
{
    // user can't deny a type
    enumTypeCycle cycleType;
    if (!m_handler->selectCycleType(cycleType) || cycleType == e_cycle_invalid) {
        return;
    }

    // user can deny adding to a stream so it become a global cycle.
    QString streamName;
    m_handler->selectStream(streamName);

    // Create cycle
    ICycle *cycle = CCycleFactory::build(cycleType);
    Q_ASSERT(cycle);
    cycle->setName(CVariableFactory::buildTemporaryName(QStringLiteral("new_cycle")));
    cycle->setLbl(tr("New cycle"));

    CVariableStream * stream = m_automate->getStream(streamName);
    m_automate->changeCycleStream(cycle, stream);

    // Edit the new cycle
    CPCWindow::openModal<CEditCycleWindow>(m_automate, cycle);
}

void CConfiguratorCycleTab::slotUpdateLayout()
{
    m_handler->layout();
}
