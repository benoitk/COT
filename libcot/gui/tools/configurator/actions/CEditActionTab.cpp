#include "CEditActionTab.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"
#include "CEditActionTabUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <IVariable.h>
#include <IAction.h>

CEditActionTab::CEditActionTab(IAction *action, QWidget *parent)
    : IConfiguratorEditTab(parent)
    , m_handler(new CEditActionTabUIHandler(scrollableWidget(), this))
{
    m_handler->layout(action);
    initBaseTab();
}

void CEditActionTab::applyProperties(const QVariant &object)
{
    IVariableObjectDescriber *describer = m_handler->describer();
    IAction *action = object.value<IAction *>();
    Q_ASSERT(action);

    // We know hard coded variable names from our describer so just use them.
    action->setLabel(describer->getVariable(QStringLiteral("label"))->toString());

    // Process properties and constants
    foreach (IVariablePtr ivar, describer->getVariables()) {
        const QString type = ivar->getName().section("_", 0, 0);
        const QString key = ivar->getName().section("_", 1);
        const bool isProperty = type == "property";
        const bool isConstant = type == "constant";

        if (isProperty) {
            const QVariant value = ivar->toVariant();
            IVariable *selectedVariable = m_handler->getVariable(ivar->getLabel());

            if (selectedVariable) {
                selectedVariable->setValue(value);
            }

            action->setParameter(key, selectedVariable);
        }
        else if (isConstant) {
            action->setParameter(key, ivar);
        }
    }
}
