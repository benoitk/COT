#include "CConfiguratorCycleTabUIHandler.h"
#include "CScrollablePagerWidget.h"
#include "CPushButton.h"
#include "CToolButton.h"
#include "CEditCycleWindow.h"
#include "CPCWindow.h"
#include "cotgui_debug.h"

#include <CAutomate.h>
#include <CVariableFactory.h>
#include <CVariableStream.h>

#include <QLabel>

CConfiguratorCycleTabUIHandler::CConfiguratorCycleTabUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
}

CConfiguratorCycleTabUIHandler::~CConfiguratorCycleTabUIHandler()
{
    CVariableFactory::deleteVariables(m_internalVariables);
}

void CConfiguratorCycleTabUIHandler::layout()
{
    CVariableFactory::deleteVariables(m_internalVariables);

    CAutomate *automate = CAutomate::getInstance();
    const QList<CVariableStream*> streams = automate->getListStreams();
    IVariablePtrList ivars;

    foreach (CVariableStream *streamVar, streams) {

        ivars << streamVar;

        foreach (ICycle *cycle, streamVar->getListCycles()) {
            if (!cycle) {
                // KDAB_TODO: Uncomment me when using final api
                //Q_ASSERT(false);
                continue;
            }

            IVariable *ivar = CVariableFactory::buildTemporary(cycle->getName(), cycle->getLabel(), type_string);
            m_internalVariables[ivar->getName()] = ivar;
            ivars << ivar;
        }
    }

    // Add fake global stream
    IVariable *streamVar = CVariableFactory::buildTemporary(QString("fake_stream"), tr("Global"), type_stream);
    m_internalVariables[streamVar->getName()] = streamVar;
    ivars << streamVar;

    foreach (ICycle *cycle, automate->getListCycles()) {
        if (!cycle) {
            // KDAB_TODO: Uncomment me when using final api
            //Q_ASSERT(false);
            continue;
        }

        // cycle is member of a stream and is already visible.
        if (m_internalVariables.contains(cycle->getName())) {
            continue;
        }

        IVariable *ivar = CVariableFactory::buildTemporary(cycle->getName(), cycle->getLabel(), type_string);
        m_internalVariables[ivar->getName()] = ivar;
        ivars << ivar;
    }

    IConfiguratorUIHandler::layout(ivars, false);
}

IVariable *CConfiguratorCycleTabUIHandler::getVariable(const QString &name) const
{
    IVariable *ivar = m_internalVariables.value(name);

    if (!ivar) {
        ivar = IConfiguratorUIHandler::getVariable(name);
    }

    return ivar;
}

int CConfiguratorCycleTabUIHandler::columnCount() const
{
    return 3;
}

QWidget *CConfiguratorCycleTabUIHandler::createWidget(int column, IVariable *ivar)
{
    const bool isStream = ivar && ivar->getType() == type_stream;

    switch (column) {
        case 0: {
            return isStream ? newLabel(ivar) : Q_NULLPTR;
        }

        case 1: {
            return isStream ? Q_NULLPTR : newButton(ivar);
        }

        case 2: {
            return isStream ? Q_NULLPTR : newDeleteButton(ivar);
        }
    }

    return Q_NULLPTR;
}

void CConfiguratorCycleTabUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void CConfiguratorCycleTabUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    const bool isStream = ivar && ivar->getType() == type_stream;

    if (isStream) {
        row.widgetAt<QLabel *>(0)->setText(ivar->getLabel());
    }
    else {
        row.widgetAt<CPushButton *>(1)->setText(ivar->getLabel());
        applyEditorConstraints(row.widgets.value(1), ivar);
    }
}

void CConfiguratorCycleTabUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(ivar->getName());
    Q_ASSERT(cycle);
    const QString streamName = cycle->getRelatedStreamName();
    const bool isGlobal = streamName.isEmpty();
    CVariableStream *streamVar = Q_NULLPTR;

    // Delete cycle
    if (isGlobal) {
        streamVar = static_cast<CVariableStream *>(getVariable(QString()));
    }
    // Become a global cycle
    else {
        streamVar = static_cast<CVariableStream *>(automate->getStream(cycle->getRelatedStreamName()));
    }

    Q_ASSERT(streamVar);
    streamVar->removeCycle(cycle->getName());
    delete m_internalVariables.take(cycle->getName());

    if (isGlobal) {
        automate->delCycle(cycle);
    }
}

void CConfiguratorCycleTabUIHandler::rowDeleted(const QString &name)
{
    Q_UNUSED(name);
    layout();
}

void CConfiguratorCycleTabUIHandler::slotEditClicked()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(editor->userData().toString());
    Q_ASSERT(cycle);
    CPCWindow::openModal<CEditCycleWindow>(cycle);
}

CPushButton *CConfiguratorCycleTabUIHandler::newButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    connect(button, &CPushButton::clicked, this, &CConfiguratorCycleTabUIHandler::slotEditClicked);
    return button;
}
