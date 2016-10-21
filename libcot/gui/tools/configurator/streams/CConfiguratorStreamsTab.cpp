#include "CConfiguratorStreamsTab.h"
#include "ConfiguratorStreamsUIHandler.h"

#include <IVariableUIHandler.h>
#include <CAutomate.h>

CConfiguratorStreamsTab::CConfiguratorStreamsTab(CAutomate* arg_automate, QWidget *parent)
    : IConfiguratorTab(parent)
{
    m_istreamUIHandler = new ConfiguratorStreamsUIHandler(arg_automate, scrollableWidget(), this);
    m_istreamUIHandler->layout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, m_istreamUIHandler, &ConfiguratorStreamsUIHandler::slotAddStreams);
    connect(arg_automate, &CAutomate::signalStreamsUpdated, m_istreamUIHandler, &ConfiguratorStreamsUIHandler::layout);

    initBaseTab();
}
