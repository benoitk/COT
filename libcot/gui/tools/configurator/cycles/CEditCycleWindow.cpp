#include "CEditCycleWindow.h"
#include "CEditCycleTab.h"
#include "CEditStepListTab.h"

#include <CAutomate.h>
#include <IVariable.h>
#include <ICycle.h>

CEditCycleWindow::CEditCycleWindow(ICycle *cycle, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(cycle), parent)
    , m_ceditCycleTab(new CEditCycleTab(cycle, this))
    , m_ceditCycleStepListTab(new CEditStepListTab(cycle, this))
{
    addTab(m_ceditCycleTab);
    addTab(m_ceditCycleStepListTab);
    initBaseWindow();
}

void CEditCycleWindow::slotRetranslate()
{
    setTabText(0, tr("General"));
    setTabText(1, tr("Steps"));
}

void CEditCycleWindow::slotOkTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = editedObject().value<ICycle *>();
    Q_ASSERT(cycle);
    const bool isNew = !automate->getListCycles().contains(cycle);
    const QVariantMap oldData = isNew ? QVariantMap() : cycle->serialise();

    applyProperties();

    if (oldData != cycle->serialise()) {
        automate->informAboutCycleChanges(cycle, oldData);
    }

    close();
}

void CEditCycleWindow::slotCancelTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = editedObject().value<ICycle *>();
    Q_ASSERT(cycle);
    const bool isNew = !automate->getListCycles().contains(cycle);

    if (isNew) {
        delete cycle;
    }

    close();
}
