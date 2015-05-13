#include "CEditOutBindsTab.h"
#include "CAutomate.h"
#include "CEditOutBindsUIHandler.h"

CEditOutBindsTab::CEditOutBindsTab(QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    m_configuratorUIHandler = new CEditOutBindsUIHandler(scrollableWidget(), this);

    initBaseTab();
}

void CEditOutBindsTab::setVariables(IVariable *ivar)
{
    Q_ASSERT(ivar);
    const QList<IVariable *> listOutBinds = ivar->getListOutBinds();
    m_configuratorUIHandler->layout(listOutBinds, true);
}

void CEditOutBindsTab::applyProperties(const QVariant &object)
{
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);
    QList<IVariable *> lstVar;
    foreach( const QString &varname, m_configuratorUIHandler->variableNames()) {
        IVariable *var = m_configuratorUIHandler->getVariable(varname);
        if (var) {
            lstVar << var;
        }
    }
    ivar->setListOutBinds(lstVar);
}

