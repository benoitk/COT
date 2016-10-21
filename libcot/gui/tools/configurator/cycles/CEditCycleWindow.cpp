#include "CEditCycleWindow.h"
#include "CEditCycleTab.h"
#include "CEditStepListTab.h"

#include <CAutomate.h>
#include <IVariable.h>
#include <ICycle.h>

CEditCycleWindow::CEditCycleWindow(CAutomate* arg_automate, ICycle *cycle, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(cycle), parent)
    , m_ceditCycleTab(new CEditCycleTab(arg_automate, cycle, this))
    , m_ceditCycleStepListTab(new CEditStepListTab(arg_automate, cycle, this))
    , m_cycle(cycle)
    , m_automate(arg_automate)
{
    addTab(m_ceditCycleTab);
    addTab(m_ceditCycleStepListTab);
    initBaseWindow();
}

void CEditCycleWindow::slotRetranslate()
{
    setTabText(0, m_cycle->getLabel());
    setTabText(1, tr("Steps"));
}

void CEditCycleWindow::slotOkTriggered()
{
    ICycle *cycle = editedObject().value<ICycle *>();
    Q_ASSERT(cycle);
    const bool isNew = !m_automate->getListCycles().contains(cycle);
    const QVariantMap oldData = isNew ? QVariantMap() : cycle->serialize();

    applyProperties();

    if (oldData != cycle->serialize()) {
        m_automate->informAboutCycleChanges(cycle, oldData);
    }

    close();
}

void CEditCycleWindow::slotCancelTriggered()
{
    ICycle *cycle = editedObject().value<ICycle *>();
    Q_ASSERT(cycle);
    const bool isNew = !m_automate->getListCycles().contains(cycle);

    if (isNew) {
        m_automate->changeCycleStream(cycle, Q_NULLPTR);
        delete cycle;
    }

    close();
}
