#include "CEditStepTab.h"
#include "IConfiguratorUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <CStep.h>

CEditStepTab::CEditStepTab(CStep *step, QWidget *parent)
    : IConfiguratorEditTab(parent)
    , m_handler(new IConfiguratorUIHandler(scrollableWidget(), this))
    , m_describer(new CVariableCStepDescriber(m_handler))
{
    m_handler->setDescriber(m_describer);
    m_describer->describe(QVariant::fromValue(step));
    m_handler->layout(m_describer->getVariables());
}

CEditStepTab::~CEditStepTab()
{
}

void CEditStepTab::applyProperties(const QVariant &object)
{
    CStep *step = object.value<CStep *>();
    Q_ASSERT(step);

    step->setNumStep(m_describer->getVariable(QStringLiteral("interval"))->toInt());
    step->setLabel(m_describer->getVariable(QStringLiteral("label"))->toString());
}
