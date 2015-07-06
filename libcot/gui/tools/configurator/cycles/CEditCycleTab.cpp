#include "CEditCycleTab.h"
#include "CScrollableWidget.h"
#include "CEditCycleTabUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <IVariable.h>
#include <CAutomate.h>

CEditCycleTab::CEditCycleTab(ICycle *cycle, QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    m_handler = new CEditCycleTabUIHandler(scrollableWidget(), this);
    m_handler->layout(cycle);

    initBaseTab();
}

void CEditCycleTab::applyProperties(const QVariant &object)
{
    CAutomate * automate = CAutomate::getInstance();
    IVariableObjectDescriber *describer = m_handler->describer();
    ICycle *cycle = object.value<ICycle *>();
    Q_ASSERT(cycle);

    // We know hard coded variable names from our describer so just use them.
    //cycle->setName(describer->getVariable(QStringLiteral("name"))->toString()); // read only
    cycle->setLbl(describer->getVariable(QStringLiteral("label"))->toString());
    //cycle->setType(eTypeCycle(describer->getVariable(QStringLiteral("type"))->toInt())); // read only
    //cycle->setTimer(describer->getVariable(QStringLiteral("timer"))->toInt()); // SERES_TODO: add api
    CVariableStream * stream = automate->getStream(describer->getVariable(QStringLiteral("stream"))->toString());

    if (automate->getCycleStream(cycle) != stream) {
        automate->changeCycleStream(cycle, stream);
    }
}
