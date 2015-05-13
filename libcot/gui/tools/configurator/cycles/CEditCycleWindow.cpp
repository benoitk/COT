#include "CEditCycleWindow.h"
#include "CEditCycleTab.h"

#include <CAutomate.h>
#include <IVariable.h>
#include <ICycle.h>

CEditCycleWindow::CEditCycleWindow(ICycle *cycle, QWidget *parent)
    : IConfiguratorEditWindow(QVariant::fromValue(cycle), parent)
    , m_ceditCycleTab(new CEditCycleTab(cycle, this))
    , m_ceditCycleStepsTab(Q_NULLPTR)
{
    addTab(m_ceditCycleTab);
    //addTab(m_ceditCycleStepsTab);
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
    // SERES_TODO: add api for changing a stream name (COT-52)
    QVariantMap oldData /*= m_cycle->serialize()*/;
    oldData[QStringLiteral("related_stream_name")] = cycle->getRelatedStreamName();

    applyProperties();
    automate->informAboutCycleChanges(cycle, oldData);
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
