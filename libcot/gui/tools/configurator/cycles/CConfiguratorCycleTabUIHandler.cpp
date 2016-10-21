#include "CConfiguratorCycleTabUIHandler.h"
#include "CScrollablePagerWidget.h"
#include "CPushButton.h"
#include "CToolButton.h"
#include "CEditCycleWindow.h"
#include "CPCWindow.h"
#include "CClickableLabel.h"
#include "cotgui_debug.h"

#include <CAutomate.h>
#include <CVariableFactory.h>
#include <CVariableStream.h>

CConfiguratorCycleTabUIHandler::CConfiguratorCycleTabUIHandler(CAutomate* arg_automate, CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(arg_automate, scrollable, parent)
    , m_automate(arg_automate)
{
}

CConfiguratorCycleTabUIHandler::~CConfiguratorCycleTabUIHandler()
{
    CVariableFactory::deleteVariables(m_internalVariables);
}

void CConfiguratorCycleTabUIHandler::layout()
{
    CVariableFactory::deleteVariables(m_internalVariables);

    const QList<CVariableStream*> streams = m_automate->getListStreams();
    IVariablePtrList ivars;

    foreach (CVariableStream *streamVar, streams) {

        ivars << streamVar;

        foreach (ICycle *cycle, streamVar->getListCycles()) {
            if (!cycle) {
                // KDAB_TODO: Uncomment me when using final api
                //Q_ASSERT(false);
                continue;
            }

            IVariable *ivar = CVariableFactory::buildTemporary(m_automate, this, cycle->getName(), cycle->getLabel(), e_type_string);
            m_internalVariables[ivar->getName()] = ivar;
            ivars << ivar;
        }
    }

    // Add fake global stream
    IVariable *streamVar = CVariableFactory::buildTemporary(m_automate, this, QString("fake_stream"), tr("Global"), e_type_stream);
    m_internalVariables[streamVar->getName()] = streamVar;
    ivars << streamVar;

    foreach (ICycle *cycle, m_automate->getListCycles()) {
        if (!cycle) {
            // KDAB_TODO: Uncomment me when using final api
            //Q_ASSERT(false);
            continue;
        }

        // cycle is member of a stream and is already visible.
        if (m_internalVariables.contains(cycle->getName())) {
            continue;
        }

        IVariable *ivar = CVariableFactory::buildTemporary(m_automate, this, cycle->getName(), cycle->getLabel(), e_type_string);
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
    const bool isStream = ivar && ivar->getType() == e_type_stream;

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
    const bool isStream = ivar && ivar->getType() == e_type_stream;

    if (isStream) {
        row.widgetAt<CClickableLabel *>(0)->setText(ivar->getLabel());
    }
    else {
        row.widgetAt<CPushButton *>(1)->setText(ivar->getLabel());
        applyEditorConstraints(row.widgets.value(1), ivar);
    }
}

void CConfiguratorCycleTabUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    ICycle *cycle = m_automate->getCycle(ivar->getName());
    Q_ASSERT(cycle);
    CVariableStream * streamVar = m_automate->getCycleStream(cycle);
    const bool isGlobal = streamVar == Q_NULLPTR;

    if (!isGlobal) {
       m_automate->changeCycleStream(cycle, Q_NULLPTR);
    }

    delete m_internalVariables.take(cycle->getName());

    if (isGlobal) {
        m_automate->delCycle(cycle);
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
    ICycle *cycle = m_automate->getCycle(editor->userData().toString());
    Q_ASSERT(cycle);
    CPCWindow::openModal<CEditCycleWindow>(m_automate, cycle);
}

CPushButton *CConfiguratorCycleTabUIHandler::newButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    connect(button, &CPushButton::clicked, this, &CConfiguratorCycleTabUIHandler::slotEditClicked);
    return button;
}
