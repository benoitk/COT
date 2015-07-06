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

CConfiguratorCycleTab::CConfiguratorCycleTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , m_handler(new CConfiguratorCycleTabUIHandler(scrollableWidget(), this))
{
    slotUpdateLayout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorCycleTab::slotAddCycle);
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsUpdated, this, &CConfiguratorCycleTab::slotUpdateLayout);
    connect(CAutomate::getInstance(), &CAutomate::signalCyclesUpdated, this, &CConfiguratorCycleTab::slotUpdateLayout);
    initBaseTab();
}

void CConfiguratorCycleTab::slotAddCycle()
{
    // user can't deny a type
    eTypeCycle cycleType;
    if (!m_handler->selectCycleType(cycleType) || cycleType == CYCLE_INVALID) {
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

    CAutomate * automate = CAutomate::getInstance();
    CVariableStream * stream = automate->getStream(streamName);
    automate->changeCycleStream(cycle, stream);

    // Edit the new cycle
    CPCWindow::openModal<CEditCycleWindow>(cycle);
}

void CConfiguratorCycleTab::slotUpdateLayout()
{
    m_handler->layout();
}
