#include "CEditOutBindsTab.h"
#include "CAutomate.h"
#include "CEditOutBindsUIHandler.h"

#include <IVariableObjectDescriber.h>

CEditOutBindsTab::CEditOutBindsTab(CAutomate* arg_automate, IVariable *ivar, QWidget *parent)
    : IConfiguratorEditTab(parent)
    , m_handler(new CEditOutBindsUIHandler(arg_automate, scrollableWidget(), this))
    , m_automate(arg_automate)
{
    Q_ASSERT(ivar);
    m_handler->layout(ivar);
    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CEditOutBindsTab::slotAddBinding);
    initBaseTab();
}

void CEditOutBindsTab::applyProperties(const QVariant &object)
{
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);

    IVariablePtrList bindings = m_automate->getVariables(m_handler->getBindingNames());
    ivar->setListOutBinds(bindings);
}

void CEditOutBindsTab::slotAddBinding()
{
    QString name;

    if (!m_handler->selectVariable(name) || name.isEmpty()) {
        return;
    }

    if (m_handler->describer()->hasValue(name)) {
        return;
    }

    QStringList names = m_handler->getBindingNames();
    names << name;
    m_handler->layout(names);
}
