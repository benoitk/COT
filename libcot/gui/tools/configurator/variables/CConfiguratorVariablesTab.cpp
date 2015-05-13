#include "CConfiguratorVariablesTab.h"
#include "ConfiguratorVariablesUIHandler.h"
#include "CPCWindow.h"
#include "CEditVariableWindow.h"

#include <CAutomate.h>
#include <CVariableFactory.h>

CConfiguratorVariablesTab::CConfiguratorVariablesTab(QWidget *parent)
    : IConfiguratorTab(parent)
{
    m_ivariableUIHandler = new ConfiguratorVariablesUIHandler(scrollableWidget(), this);
    slotUpdateLayout();

    connect(m_ivariableUIHandler, &ConfiguratorVariablesUIHandler::editVariable, this, &CConfiguratorVariablesTab::editVariable);
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged, this, &CConfiguratorVariablesTab::slotUpdateLayout);
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsUpdated, this, &CConfiguratorVariablesTab::slotUpdateLayout);
    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorVariablesTab::slotAddVariable);
    initBaseTab();
}

void CConfiguratorVariablesTab::slotUpdateLayout()
{
    m_ivariableUIHandler->layout();
}

void CConfiguratorVariablesTab::slotAddVariable()
{
    QString streamName;

    if (!m_ivariableUIHandler->selectStream(streamName) || streamName.isEmpty()) {
        return;
    }
    variableType varType;
    if (!m_ivariableUIHandler->selectVariableType(varType) || (varType == type_unknow)) {
        return;
    }

    // Create variable
    IVariable *variable = CVariableFactory::build(varType);
    variable->setName(QStringLiteral("new_variable_%1").arg(qrand() %1000));
    variable->setLabel(tr("New variable"));
    variable->setRelatedStreamName(streamName);

    // Edit variable
    CPCWindow::openModal<CEditVariableWindow>(variable);
}

void CConfiguratorVariablesTab::editVariable(const QString &variableName)
{
    IVariable *ivar = CAutomate::getInstance()->getVariable(variableName);
    CPCWindow::openModal<CEditVariableWindow>(ivar);
}
