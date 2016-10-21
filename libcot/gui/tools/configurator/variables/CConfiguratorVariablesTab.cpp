#include "CConfiguratorVariablesTab.h"
#include "ConfiguratorVariablesUIHandler.h"
#include "CPCWindow.h"
#include "CEditVariableWindow.h"

#include <CAutomate.h>
#include <CVariableFactory.h>

CConfiguratorVariablesTab::CConfiguratorVariablesTab(CAutomate* arg_automate, QWidget *parent)
    : IConfiguratorTab(parent)
    , m_automate(arg_automate)
{
    m_ivariableUIHandler = new ConfiguratorVariablesUIHandler(arg_automate, scrollableWidget(), this);
    m_ivariableUIHandler->layout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorVariablesTab::slotAddVariable);
    connect(m_ivariableUIHandler, &ConfiguratorVariablesUIHandler::editVariable, this, &CConfiguratorVariablesTab::editVariable);
    initBaseTab();
}

void CConfiguratorVariablesTab::slotAddVariable()
{

    enumVariableType varType;
    if (!m_ivariableUIHandler->selectVariableType(varType) || (varType == e_type_unknow)) {
        return;
    }

    enumVariableOrganType organType = e_type_organ_none;
    m_ivariableUIHandler->selectOrganType(organType);

    QString name;
    m_ivariableUIHandler->selectStreamOrMeasure(name);

    // Create variable
    IVariable *variable = CVariableFactory::build(m_automate, this, varType, organType);
    variable->setName(CVariableFactory::buildTemporaryName(QStringLiteral("new_variable")));
    variable->setLabel(tr("New variable"));

    CVariableStream *stream = m_automate->getStream(name);
    CVariableMeasure *measure = m_automate->getMeasure(name);

    if (measure) {
        m_automate->changeVariableMeasure(variable, measure);
    }
    else if (stream) {
        m_automate->changeVariableStream(variable, stream);
    }

    // Edit variable
    CPCWindow::openModal<CEditVariableWindow>(m_automate, variable);
}

void CConfiguratorVariablesTab::editVariable(const QString &variableName)
{
    IVariable *ivar = m_automate->getVariable(variableName);
    if(ivar && (ivar->getType() != e_type_unknow))
        CPCWindow::openModal<CEditVariableWindow>(m_automate, ivar);
}
