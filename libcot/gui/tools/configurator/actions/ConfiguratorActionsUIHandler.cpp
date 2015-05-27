#include "ConfiguratorActionsUIHandler.h"

#include <CAutomate.h>
#include <CPushButton.h>
#include <CPCWindow.h>
#include <CToolButton.h>
#include <CVariableFactory.h>
#include <IAction.h>
#include <cotgui_debug.h>
#include <CEditActionWindow.h>

ConfiguratorActionsUIHandler::ConfiguratorActionsUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
}

ConfiguratorActionsUIHandler::~ConfiguratorActionsUIHandler()
{
    CVariableFactory::deleteVariables(m_internalVariables);
}

void ConfiguratorActionsUIHandler::layout()
{
    CVariableFactory::deleteVariables(m_internalVariables);
    IVariablePtrList ivars;

    CAutomate *automate = CAutomate::getInstance();
    const QList<IAction *> actions = automate->getListActions();
    foreach ( IAction *action, actions ) {
        // All this assumes that actions have a unique name. But of course so does CAutomate::getAction.
        qCDebug(COTGUI_LOG) << action->getName() << action->getLabel();
        IVariable *ivar = CVariableFactory::buildTemporary(action->getName(), action->getLabel(), type_string);
        if (m_internalVariables.contains(action->getName())) {
            qWarning(COTGUI_LOG) << "Already have an action called" << action->getName();
        }
        m_internalVariables.insert(action->getName(), ivar);
        ivars << ivar;
    }

    IConfiguratorUIHandler::layout(ivars, true);
}

int ConfiguratorActionsUIHandler::columnCount() const
{
    return 2;
}

QWidget *ConfiguratorActionsUIHandler::createWidget(int column, IVariable *ivar)
{
    switch (column) {
    case 0:
        return newButton(ivar);
    case 1:
        return newDeleteButton(ivar);
    }
    return Q_NULLPTR;
}

void ConfiguratorActionsUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(ivar);
    connect(row.widgetAt<CPushButton *>(0), &CPushButton::clicked, this, & ConfiguratorActionsUIHandler::slotEditClicked);
}

void ConfiguratorActionsUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    row.widgetAt<QPushButton *>(0)->setText(ivar->getLabel());
    applyEditorConstraints(row.widgets.value(0), ivar);
}

void ConfiguratorActionsUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    CAutomate *automate = CAutomate::getInstance();
    const QString actionName = ivar->getName();
    m_internalVariables.take(actionName);
    IAction *action = automate->getAction(actionName);
    Q_ASSERT(action);
    // SERES_TODO automate->delAction(action); // COT-60
    qWarning() << "Not fully implemented, missing API for removeAction";
    delete ivar;
}

void ConfiguratorActionsUIHandler::rowDeleted(const QString &name)
{
    Q_UNUSED(name);
    layout();
}

IVariable *ConfiguratorActionsUIHandler::getVariable(const QString &name) const
{
    return m_internalVariables.value(name);
}

void ConfiguratorActionsUIHandler::slotEditClicked()
{
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    CAutomate *automate = CAutomate::getInstance();
    IAction *action = automate->getAction(editor->userData().toString());
    Q_ASSERT(action);
    qCDebug(COTGUI_LOG) << "Editing action" << action << action->getName();
    // KDAB_TODO
    CPCWindow::openModal<CEditActionWindow>(action);
}

CPushButton *ConfiguratorActionsUIHandler::newButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    return button;
}
