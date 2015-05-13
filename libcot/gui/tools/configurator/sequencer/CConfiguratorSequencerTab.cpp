#include "CConfiguratorSequencerTab.h"
#include "ConfiguratorSequencerUIHandler.h"

#include <CAutomate.h>
#include <CSequencer.h>

CConfiguratorSequencerTab::CConfiguratorSequencerTab(QWidget *parent)
    : IConfiguratorTab(parent)
{
    m_isequencerUIHandler = new ConfiguratorSequencerUIHandler(scrollableWidget(), this);
    slotUpdateLayout();

    connect(CAutomate::getInstance(), &CAutomate::signalSchedulerUpdated, this, &CConfiguratorSequencerTab::slotUpdateLayout);
    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorSequencerTab::slotAddSequencer);
    initBaseTab();
}

void CConfiguratorSequencerTab::slotUpdateLayout()
{
    m_isequencerUIHandler->layout();
}

void CConfiguratorSequencerTab::slotAddSequencer()
{
    QString cycleName;
    int value = 1;

    if (!m_isequencerUIHandler->selectCycle(cycleName) || cycleName.isEmpty()) {
        return;
    }

    if (!m_isequencerUIHandler->enterInteger(value) || value <= 0) {
        return;
    }

    CAutomate *automate = CAutomate::getInstance();
    CSequencer *sequencer = CSequencer::getInstance();
    ICycle *cycle = automate->getCycle(cycleName);
    Q_ASSERT(cycle);

    sequencer->addCycle(qMakePair(cycle, value));
}
