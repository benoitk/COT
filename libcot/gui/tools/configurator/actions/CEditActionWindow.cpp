#include "CEditActionWindow.h"
#include "CEditActionTab.h"

#include <CAutomate.h>
#include <IVariable.h>
#include <IAction.h>

CEditActionWindow::CEditActionWindow(IAction *action, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(action), parent)
    , m_ceditActionTab(new CEditActionTab(action, this))
    , m_ceditActionStepsTab(Q_NULLPTR)
    , m_action(action)
{
    addTab(m_ceditActionTab);
    //addTab(m_ceditActionStepsTab);
    initBaseWindow();
}

void CEditActionWindow::slotRetranslate()
{
    setTabText(0, m_action->getLabel());
    setTabText(1, tr("Steps"));
}


void CEditActionWindow::slotOkTriggered()
{
    CAutomate *automate = CAutomate::getInstance();

    applyProperties();

//    automate->informAboutActionChanges(m_action, oldData);
    close();
}

void CEditActionWindow::slotCancelTriggered()
{
    IAction *action = editedObject().value<IAction *>();
    Q_ASSERT(action);
    CAutomate *automate = CAutomate::getInstance();
    const bool isNew = !automate->getListActions().contains(action);

    if (isNew) {
        delete action;
    }

    close();
}
