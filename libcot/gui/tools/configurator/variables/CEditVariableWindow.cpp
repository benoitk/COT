#include "CEditVariableWindow.h"
#include "CEditInBindsTab.h"
#include "CEditOutBindsTab.h"
#include "CEditVariableTab.h"
#include "CAutomate.h"
#include <IVariable.h>

CEditVariableWindow::CEditVariableWindow(IVariable *ivar, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(ivar), parent)
    , m_ceditVariableTab(new CEditVariableTab(this))
    , m_ceditOutBindsTab(new CEditOutBindsTab(this))
    , m_ceditInBindsTab(new CEditInBindsTab(this))
{
    addTab(m_ceditVariableTab);
    addTab(m_ceditOutBindsTab);
    addTab(m_ceditInBindsTab);
    initBaseWindow();
    if (ivar) {
        setVariables(ivar);
    }
}

void CEditVariableWindow::setVariables(IVariable *ivar)
{
    m_ceditVariableTab->setVariables(ivar);
    m_ceditOutBindsTab->setVariables(ivar);
    m_ceditInBindsTab->setVariables(ivar);
}

void CEditVariableWindow::slotRetranslate()
{
   setTabText(0, tr("Variables"));
   setTabText(1, tr("Out Binds"));
   setTabText(2, tr("In Binds"));
}

void CEditVariableWindow::slotCancelTriggered()
{
    IVariable *variable = editedObject().value<IVariable *>();
    Q_ASSERT(variable);
    const bool isNew = CAutomate::getInstance()->getMapVariables().values().contains(variable);

    if (isNew) {
        delete variable;
    }
    close();
}

void CEditVariableWindow::slotOkTriggered()
{
    IVariable *variable = editedObject().value<IVariable *>();
    Q_ASSERT(variable);
    CAutomate *automate = CAutomate::getInstance();
    applyProperties();
    //TODO implement it.
    //automate->informAboutVariableChanges(variable, oldmap);
    close();
}
