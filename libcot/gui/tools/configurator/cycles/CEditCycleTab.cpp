#include "CEditCycleTab.h"
#include "CScrollableWidget.h"
#include "CEditCycleTabUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <IVariable.h>
#include <CAutomate.h>

CEditCycleTab::CEditCycleTab(CAutomate* arg_automate, ICycle *cycle, QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    m_handler = new CEditCycleTabUIHandler(arg_automate, scrollableWidget(), this);
    m_handler->layout(cycle);

    initBaseTab();
}

void CEditCycleTab::applyProperties(const QVariant &object)
{
    IVariableObjectDescriber *describer = m_handler->describer();
    ICycle *cycle = object.value<ICycle *>();
    Q_ASSERT(cycle);

    // We know hard coded variable names from our describer so just use them.
    //cycle->setName(describer->getVariable(QStringLiteral("name"))->toString()); // read only
    cycle->setLbl(describer->getVariable(QStringLiteral("label"))->toString());
    //cycle->setType(eTypeCycle(describer->getVariable(QStringLiteral("type"))->toInt())); // read only
    //cycle->setTimer(describer->getVariable(QStringLiteral("timer"))->toInt()); // SERES_TODO: add api
    CVariableStream * stream = m_automate->getStream(describer->getVariable(QStringLiteral("stream"))->toString());

    if (m_automate->getCycleStream(cycle) != stream) {
        m_automate->changeCycleStream(cycle, stream);
    }
}
