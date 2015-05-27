#include "CConfiguratorStreamsTab.h"
#include "ConfiguratorStreamsUIHandler.h"

#include <IVariableUIHandler.h>
#include <CAutomate.h>

CConfiguratorStreamsTab::CConfiguratorStreamsTab(QWidget *parent)
    : IConfiguratorTab(parent)
{

    m_istreamUIHandler = new ConfiguratorStreamsUIHandler(scrollableWidget(), this);
    m_istreamUIHandler->layout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, m_istreamUIHandler, &ConfiguratorStreamsUIHandler::slotAddStreams);
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsUpdated, m_istreamUIHandler, &ConfiguratorStreamsUIHandler::layout);

    initBaseTab();
}
