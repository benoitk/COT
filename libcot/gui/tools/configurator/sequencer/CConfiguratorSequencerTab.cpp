#include "CConfiguratorSequencerTab.h"
#include "ConfiguratorSequencerUIHandler.h"

CConfiguratorSequencerTab::CConfiguratorSequencerTab(QWidget *parent)
    : IConfiguratorTab(parent)
{
    m_isequencerUIHandler = new ConfiguratorSequencerUIHandler(scrollableWidget(), this);
    m_isequencerUIHandler->layout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorSequencerTab::slotAddSequencer);
    initBaseTab();
}

void CConfiguratorSequencerTab::slotAddSequencer()
{
    QString newCycleName;

    if (m_isequencerUIHandler->selectCycle(newCycleName) && !newCycleName.isEmpty()) {
        //TODO add new cycle.
    }
}
