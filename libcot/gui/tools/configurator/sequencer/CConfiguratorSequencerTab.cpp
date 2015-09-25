#include "CConfiguratorSequencerTab.h"
#include "ConfiguratorSequencerUIHandler.h"

#include <CAutomate.h>

CConfiguratorSequencerTab::CConfiguratorSequencerTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , m_handler(new ConfiguratorSequencerUIHandler(scrollableWidget(), this))
{
    slotUpdateLayout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorSequencerTab::slotAddSequencer);
    connect(CAutomate::getInstance(), &CAutomate::signalSchedulerUpdated, this, &CConfiguratorSequencerTab::slotUpdateLayout);
    initBaseTab();
}

void CConfiguratorSequencerTab::slotUpdateLayout()
{
    m_handler->layout();
}

void CConfiguratorSequencerTab::slotAddSequencer()
{
    QString cycleName;
    int count = 1;

    if (!m_handler->selectCycle(cycleName) || cycleName.isEmpty()) {
        return;
    }

    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(cycleName);
    Q_ASSERT(cycle);

    if (cycle->getType() != e_cycle_measure) {
        return;
    }

    if (!m_handler->enterInteger(count) || count <= 0) {
        return;
    }

    ConfiguratorSequencerUIHandler::CyclePairList pairs = m_handler->cyclePairList();

    if (pairs.isEmpty() || pairs.last().first != cycle) {
        pairs << qMakePair(cycle, count);
    }
    else {
        pairs.last().second += count;
    }

    m_handler->setCyclePairList(pairs);
}
