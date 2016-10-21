#include "CEditVariableWindow.h"
#include "CEditInBindsTab.h"
#include "CEditOutBindsTab.h"
#include "CEditVariableTab.h"
#include "CAutomate.h"
#include <IVariable.h>

CEditVariableWindow::CEditVariableWindow(CAutomate* arg_automate, IVariable *ivar, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(ivar), parent)
    , m_variable(ivar)
    , m_automate(arg_automate)
{
    addTab(new CEditVariableTab(arg_automate, ivar, this));
    addTab(new CEditOutBindsTab(arg_automate, ivar, this));
    addTab(new CEditInBindsTab(arg_automate, ivar, this));

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
    IVariable *variable = editedObject().value<IVariable *>();
    Q_ASSERT(variable);
    const bool isNew = !m_automate->getMapVariables().values().contains(variable);
    if (isNew) {
        m_automate->changeVariableMeasure(variable, Q_NULLPTR);
        m_automate->changeVariableStream(variable, Q_NULLPTR);
        delete variable;
    }
    close();
}

void CEditVariableWindow::slotOkTriggered()
{
    IVariable *variable = editedObject().value<IVariable *>();
    Q_ASSERT(variable);
    const QVariantMap oldVarMap = variable->serialize();
    applyProperties();
    m_automate->informAboutVariableChanges(variable, oldVarMap);
    close();
}
