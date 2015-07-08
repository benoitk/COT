#include "CEditOutBindsTab.h"
#include "CAutomate.h"
#include "CEditOutBindsUIHandler.h"

#include <IVariableObjectDescriber.h>

CEditOutBindsTab::CEditOutBindsTab(IVariable *ivar, QWidget *parent)
    : IConfiguratorEditTab(parent)
    , m_handler(new CEditOutBindsUIHandler(scrollableWidget(), this))
{
    Q_ASSERT(ivar);
    m_handler->layout(ivar);
    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CEditOutBindsTab::slotAddBinding);
    initBaseTab();
}

void CEditOutBindsTab::applyProperties(const QVariant &object)
{
    CAutomate * automate = CAutomate::getInstance();
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);

    IVariablePtrList bindings = automate->getVariables(m_handler->getBindingNames());
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
