#include "CEditVariableWindow.h"
#include "CEditInBindsTab.h"
#include "CEditOutBindsTab.h"
#include "CEditVariableTab.h"
#include "CAutomate.h"
#include <IVariable.h>

CEditVariableWindow::CEditVariableWindow(IVariable *ivar, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(ivar), parent)
    , m_variable(ivar)
{
    addTab(new CEditVariableTab(ivar, this));
    addTab(new CEditOutBindsTab(ivar, this));
    addTab(new CEditInBindsTab(ivar, this));

    initBaseWindow();
}

void CEditVariableWindow::slotRetranslate()
{
   setTabText(0, m_variable->getLabel());
   setTabText(1, tr("Out Binds"));
   setTabText(2, tr("In Binds"));
}

void CEditVariableWindow::slotCancelTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    IVariable *variable = editedObject().value<IVariable *>();
    Q_ASSERT(variable);
    const bool isNew = !CAutomate::getInstance()->getMapVariables().values().contains(variable);
    if (isNew) {
        automate->changeVariableMeasure(variable, Q_NULLPTR);
        automate->changeVariableStream(variable, Q_NULLPTR);
        delete variable;
    }
    close();
}

void CEditVariableWindow::slotOkTriggered()
{
    IVariable *variable = editedObject().value<IVariable *>();
    Q_ASSERT(variable);
    const QVariantMap oldVarMap = variable->serialize();
    CAutomate *automate = CAutomate::getInstance();
    applyProperties();
    automate->informAboutVariableChanges(variable, oldVarMap);
    close();
}
