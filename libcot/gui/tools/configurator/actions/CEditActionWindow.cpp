#include "CEditActionWindow.h"
#include "CEditActionTab.h"
#include "CEditStepListTab.h"

#include <CAutomate.h>
#include <IVariable.h>
#include <IAction.h>
#include <CActionBlock.h>
#include <CCycleAutonome.h>

CEditActionWindow::CEditActionWindow(CAutomate* arg_automate, IAction *action, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(action), parent)
    , m_ceditActionTab(new CEditActionTab(arg_automate, action, this))
    , m_ceditActionStepsTab(Q_NULLPTR)
    , m_action(action)
    , m_automate(arg_automate)
{
    addTab(m_ceditActionTab);

    if (action->getType() == type_block) {
        CActionBlock *ab = qobject_cast<CActionBlock *>(action);
        m_ceditActionStepsTab = new CEditStepListTab(arg_automate, ab->getCycle(), this);
        addTab(m_ceditActionStepsTab);
    }
    initBaseWindow();
}

void CEditActionWindow::applyProperties()
{
    m_ceditActionTab->applyProperties(editedObject());

    if (m_ceditActionStepsTab) {
        CActionBlock *ab = editedObject().value<CActionBlock *>();
        m_ceditActionStepsTab->applyProperties(QVariant::fromValue(ab->getCycle()));
    }
}

void CEditActionWindow::slotRetranslate()
{
    setTabText(0, m_action->getLabel());
    setTabText(1, tr("Steps"));
}

void CEditActionWindow::slotOkTriggered()
{
    applyProperties();

    IAction *action = editedObject().value<IAction *>();
    Q_ASSERT(action);
    const bool isNew = !m_automate->getListActions().contains(action);

    if (isNew) {
        m_automate->addAction(action, true);
    }

    close();
}

void CEditActionWindow::slotCancelTriggered()
{
    IAction *action = editedObject().value<IAction *>();
    Q_ASSERT(action);
    const bool isNew = !m_automate->getListActions().contains(action);

    if (isNew) {
        delete action;
    }

    close();
}
