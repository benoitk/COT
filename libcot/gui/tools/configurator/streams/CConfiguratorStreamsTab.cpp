#include "CConfiguratorStreamsTab.h"
#include "ConfiguratorStreamsUIHandler.h"

#include <IVariableUIHandler.h>

CConfiguratorStreamsTab::CConfiguratorStreamsTab(QWidget *parent)
    : IConfiguratorTab(parent)
{
    
    m_istreamUIHandler = new ConfiguratorStreamsUIHandler(scrollableWidget(), this);
    m_istreamUIHandler->layout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorStreamsTab::slotAddStreams);
    initBaseTab();
}

void CConfiguratorStreamsTab::slotAddStreams()
{
}
