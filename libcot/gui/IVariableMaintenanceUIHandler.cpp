#include "IVariableMaintenanceUIHandler.h"
#include "CScrollableWidget.h"
#include "CToolButton.h"
#include "CAutomate.h"
#include "ICycle.h"
#include "CVariableString.h"

#include <QLabel>

IVariableMaintenanceUIHandler::IVariableMaintenanceUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IVariableUIHandler(scrollable, parent)
{
    CAutomate *automate = CAutomate::getInstance();
    connect(automate, &CAutomate::signalCycleChanged, this, &IVariableMaintenanceUIHandler::slotCycleChanged);
}

void IVariableMaintenanceUIHandler::layout()
{
    CAutomate *automate = CAutomate::getInstance();
    QList<ICycle *> cycles = automate->getListCycles(CYCLE_MAINTENANCE);
    IVariablePtrList variables;

    foreach (ICycle *cycle, cycles) {
        IVariable *variable = new CVariableString;
        variable->setName(cycle->getName());
        variable->setLabel(cycle->getLbl());
        variables << variable;
    }

    IVariableUIHandler::layout(variables);
    qDeleteAll(variables);
}

int IVariableMaintenanceUIHandler::columnCount() const
{
    return 3;
}

QWidget *IVariableMaintenanceUIHandler::createWidget(int index, IVariable *ivar)
{
    switch (index) {
        case 0:
            return newLabel(ivar);

        case 1:
            return newStartEditor(ivar);

        case 2:
            return newStopEditor(ivar);
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void IVariableMaintenanceUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(ivar);
    connect(row.widgetAt<CToolButton *>(1), &CToolButton::clicked,
            this, &IVariableMaintenanceUIHandler::slotButtonStartClicked);
    connect(row.widgetAt<CToolButton *>(2), &CToolButton::clicked,
            this, &IVariableMaintenanceUIHandler::slotButtonStopClicked);
}

void IVariableMaintenanceUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(ivar->getName(), CYCLE_MAINTENANCE);

    if (!cycle) {
        Q_ASSERT(false);
        return;
    }

    row.widgetAt<QLabel *>(0)->setText(cycle->getLbl());
    row.widgetAt<CToolButton *>(1)->setEnabled(!cycle->isRunning());
    row.widgetAt<CToolButton *>(1)->setChecked(cycle->isRunning());
    row.widgetAt<CToolButton *>(2)->setVisible(cycle->isRunning());
}

QLabel *IVariableMaintenanceUIHandler::newLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    QLabel *label = new QLabel(m_container);
    return label;
}

CToolButton *IVariableMaintenanceUIHandler::newStartEditor(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CToolButton *button = new CToolButton(CToolButton::Play, m_container);
    button->setFixedSize(30, 30);
    button->setCheckable(true);
    return button;
}

CToolButton *IVariableMaintenanceUIHandler::newStopEditor(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CToolButton *button = new CToolButton(CToolButton::Stop, m_container);
    button->setFixedSize(30, 30);
    return button;
}

void IVariableMaintenanceUIHandler::slotCycleChanged(const QString &name)
{
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(name, CYCLE_MAINTENANCE);

    if (!m_rows.contains(name) || !cycle) {
        return;
    }

    rowChanged(m_rows[name], Q_NULLPTR);
}

void IVariableMaintenanceUIHandler::slotButtonStartClicked()
{
    const CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString cycleName = button->userData().toString();
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(cycleName, CYCLE_MAINTENANCE);

    if (!m_rows.contains(cycleName) || !cycle) {
        Q_ASSERT(false);
        return;
    }

    if (cycle->isPaused()) {
        cycle->slotUnPauseCycle();
    }
    else if (cycle->isRunning()) {
        cycle->slotPauseCycle();
    }
    else {
        cycle->slotRunCycle();
    }
}

void IVariableMaintenanceUIHandler::slotButtonStopClicked()
{
    const CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString cycleName = button->userData().toString();
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(cycleName, CYCLE_MAINTENANCE);

    if (!m_rows.contains(cycleName) || !cycle) {
        Q_ASSERT(false);
        return;
    }

    if (cycle->isRunning()) {
        cycle->slotStopCycle();
    }
}
