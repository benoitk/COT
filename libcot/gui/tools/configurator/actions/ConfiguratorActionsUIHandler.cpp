#include "ConfiguratorActionsUIHandler.h"
#include "CScrollablePagerWidget.h"

#include <CAutomate.h>
#include <CPushButton.h>
#include <CPCWindow.h>
#include <CToolButton.h>
#include <CVariableFactory.h>
#include <CVariableMutable.h>
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

    CAutomate *automate = CAutomate::getInstance();
    const QList<IAction *> actions = automate->getListActions();
    IVariablePtrList ivars;

    foreach (IAction *action, actions) {
        // All this assumes that actions have a unique name. But of course so does CAutomate::getAction.
        QString actionName = action->getName();
        QString actionLbl = action->getLabel();
        CVariableMutable *ivar = qobject_cast<CVariableMutable *>(CVariableFactory::buildTemporary(actionName, actionLbl, type_mutable));
        ivar->setAccess(access_read_write);

        if (m_internalVariables.contains(action->getName())) {
            qWarning(COTGUI_LOG) << "Already have an action called" << action->getName();
            Q_ASSERT(false);
        }

        m_internalVariables.insert(action->getName(), ivar);
        ivars << ivar;
    }

    IConfiguratorUIHandler::layout(ivars);
}

int ConfiguratorActionsUIHandler::columnCount() const
{
    return 2;
}

QWidget *ConfiguratorActionsUIHandler::createWidget(int column, IVariable *ivar)
{
    switch (column) {
        case 0:
            return newEditor(ivar);

        case 1:
            return newDeleteButton(ivar);
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void ConfiguratorActionsUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(ivar);
    connect(row.widgetAt<CPushButton *>(0), &CPushButton::clicked, this, & ConfiguratorActionsUIHandler::slotEditClicked);
}

void ConfiguratorActionsUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    applyEditorConstraints(row.widgets.value(0), ivar);
    row.widgetAt<CPushButton *>(0)->setText(ivar->getLabel());
}

void ConfiguratorActionsUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    CAutomate *automate = CAutomate::getInstance();
    const QString actionName = ivar->getName();
    m_internalVariables.take(actionName);
    IAction *action = automate->getAction(actionName);
    Q_ASSERT(action);
    automate->delAction(action);
    delete ivar;
}

void ConfiguratorActionsUIHandler::rowDeleted(const QString &name)
{
    Q_UNUSED(name);
}

IVariable *ConfiguratorActionsUIHandler::getVariable(const QString &name) const
{
    return m_internalVariables.value(name);
}

void ConfiguratorActionsUIHandler::slotEditClicked()
{
    CAutomate *automate = CAutomate::getInstance();
    CPushButton *editor = qobject_cast<CPushButton *>(sender());
    IAction *action = automate->getAction(editor->userData().toString());
    Q_ASSERT(action);
    CPCWindow::openModal<CEditActionWindow>(action);
}
