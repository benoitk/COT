#include "CEditActionWindow.h"
#include "CEditActionTab.h"

#include <CAutomate.h>
#include <IVariable.h>
#include <IAction.h>

CEditActionWindow::CEditActionWindow(IAction *action, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(action), parent)
    , m_ceditActionTab(new CEditActionTab(action, this))
    , m_ceditActionStepsTab(Q_NULLPTR)
{
    addTab(m_ceditActionTab);
    //addTab(m_ceditActionStepsTab);
    initBaseWindow();
}

void CEditActionWindow::slotRetranslate()
{
    setTabText(0, tr("General"));
    setTabText(1, tr("Steps"));
}


void CEditActionWindow::slotOkTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    // SERES_TODO: add api for IAction serialisation
//    QVariantMap oldData /*= m_action->serialize()*/;
//    oldData[QStringLiteral("related_stream_name")] = m_action->getRelatedStreamName();

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
