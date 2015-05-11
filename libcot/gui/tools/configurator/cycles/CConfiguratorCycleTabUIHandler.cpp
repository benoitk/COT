#include "CConfiguratorCycleTabUIHandler.h"
#include "CPushButton.h"
#include "CToolButton.h"
#include "CEditCycleWindow.h"
#include "CPCWindow.h"

#include <CAutomate.h>
#include <CVariableFactory.h>
#include <CVariableStream.h>

#include <QLabel>
#include <QDebug>

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
    const IVariablePtrList streams = automate->getMapStreams().values();
    IVariablePtrList ivars;

    foreach ( IVariable *streamIVar, streams) {
        Q_ASSERT(streamIVar->getType() == type_stream);
        CVariableStream *streamVar = static_cast<CVariableStream *>(streamIVar);

        ivars << streamVar;

        foreach (ICycle *cycle, streamVar->getListCycles()) {
            if (!cycle) {
                // KDAB_TODO: Uncomment me when using final api
                //Q_ASSERT(false);
                continue;
            }

            IVariable *ivar = CVariableFactory::buildTemporary(cycle->getName(), cycle->getLbl(), type_string);
            m_internalVariables[cycle->getName()] = ivar;
            ivars << ivar;
        }
    }

    IConfiguratorUIHandler::layout(ivars, true);
}

IVariable *CConfiguratorCycleTabUIHandler::getVariable(const QString &name)
{
    IVariable *ivar = m_internalVariables.value(name);

    if (!ivar) {
        ivar = IConfiguratorUIHandler::getVariable(name);
    }

    return ivar;
}

int CConfiguratorCycleTabUIHandler::columnCount() const
{
    return 2;
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
    const bool isStream = ivar && ivar->getType() == type_stream;

    if (isStream) {
    }
    else {
        connect(row.widgetAt<CPushButton *>(1), &CPushButton::clicked, this, & CConfiguratorCycleTabUIHandler::slotEditClicked);
        connect(row.widgetAt<CToolButton *>(2), &CToolButton::clicked, this, & CConfiguratorCycleTabUIHandler::slotDeleteClicked);
    }
}

void CConfiguratorCycleTabUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    const bool isStream = ivar && ivar->getType() == type_stream;

    if (isStream) {
        row.widgetAt<QLabel *>(0)->setText(ivar->getLabel());
    }
    else {
        row.widgetAt<CPushButton *>(1)->setText(ivar->getLabel());
    }
}

void CConfiguratorCycleTabUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(ivar->getName());
    Q_ASSERT(cycle);
    const QString streamName = cycle->getRelatedStreamName();
    CVariableStream *streamVar = static_cast<CVariableStream *>(automate->getMapStreams().value(streamName));
    Q_ASSERT(streamVar);
    streamVar->delCycle(cycle->getName());
    delete m_internalVariables.take(ivar->getName());
}

void CConfiguratorCycleTabUIHandler::slotEditClicked()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(editor->userData().toString());

    Q_ASSERT(cycle);

    CPCWindow::openModal<CEditCycleWindow>(CyclePair(cycle->getRelatedStreamName(), cycle));
}

CPushButton *CConfiguratorCycleTabUIHandler::newButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    return button;
}
