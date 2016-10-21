#include "CConfiguratorSequencerTab.h"
#include "ConfiguratorSequencerUIHandler.h"

#include <CAutomate.h>

CConfiguratorSequencerTab::CConfiguratorSequencerTab(CAutomate* arg_automate, QWidget *parent)
    : IConfiguratorTab(parent)
    , m_handler(new ConfiguratorSequencerUIHandler(arg_automate, scrollableWidget(), this))
    , m_automate(arg_automate)
{
    slotUpdateLayout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorSequencerTab::slotAddSequencer);
    connect(m_automate, &CAutomate::signalSchedulerUpdated, this, &CConfiguratorSequencerTab::slotUpdateLayout);
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

    ICycle *cycle = m_automate->getCycle(cycleName);
    Q_ASSERT(cycle);

    if (cycle->getType() != e_cycle_measure && cycle->getType() != e_cycle_pause) {
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
