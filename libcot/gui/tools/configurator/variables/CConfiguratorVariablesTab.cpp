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

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorVariablesTab::slotAddVariable);
    connect(m_ivariableUIHandler, &ConfiguratorVariablesUIHandler::editVariable, this, &CConfiguratorVariablesTab::editVariable);
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsUpdated, this, &CConfiguratorVariablesTab::slotUpdateLayout);
    connect(CAutomate::getInstance(), &CAutomate::signalVariablesUpdated, this, &CConfiguratorVariablesTab::slotUpdateLayout);
    initBaseTab();
}

void CConfiguratorVariablesTab::slotUpdateLayout()
{
    m_ivariableUIHandler->layout();
}

void CConfiguratorVariablesTab::slotAddVariable()
{
    CAutomate *automate = CAutomate::getInstance();

    QString name;
    if (!m_ivariableUIHandler->selectStreamOrMeasure(name) || name.isEmpty()) {
        return;
    }

    variableType varType;
    if (!m_ivariableUIHandler->selectVariableType(varType) || (varType == type_unknow)) {
        return;
    }

    VariableOrganType organType = type_organ_none;
    m_ivariableUIHandler->selectOrganType(organType);

    // Create variable
    IVariable *variable = CVariableFactory::build(varType, organType);
    variable->setName(CVariableFactory::buildTemporaryName(QStringLiteral("new_variable")));
    variable->setLabel(tr("New variable"));

    CVariableStream *stream = automate->getStream(name);
    CVariableMeasure *measure = automate->getMeasure(name);

    if (measure) {
        automate->changeVariableMeasure(variable, measure);
    }
    else if (stream) {
        automate->changeVariableStream(variable, stream);
    }

    // Edit variable
    CPCWindow::openModal<CEditVariableWindow>(variable);
}

void CConfiguratorVariablesTab::editVariable(const QString &variableName)
{
    IVariable *ivar = CAutomate::getInstance()->getVariable(variableName);
    CPCWindow::openModal<CEditVariableWindow>(ivar);
}
