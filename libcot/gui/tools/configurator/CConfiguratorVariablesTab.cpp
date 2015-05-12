#include "CConfiguratorVariablesTab.h"
#include "ui_CConfiguratorVariablesTab.h"
#include "CPCWindow.h"
#include "CEditVariableWindow.h"
#include "CAutomate.h"
#include <ConfiguratorVariablesUIHandler.h>

CConfiguratorVariablesTab::CConfiguratorVariablesTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorVariablesTab)
{
    ui->setupUi(this);
    m_ivariableUIHandler = new ConfiguratorVariablesUIHandler(ui->swCentral, this);
    slotUpdateLayout();
    connect(m_ivariableUIHandler, &ConfiguratorVariablesUIHandler::editVariable,
            this, &CConfiguratorVariablesTab::editVariable);
    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered,
            this, &CConfiguratorVariablesTab::slotAddVariable);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged,
            this, &CConfiguratorVariablesTab::slotUpdateLayout);
}

CConfiguratorVariablesTab::~CConfiguratorVariablesTab()
{
    delete ui;
}

void CConfiguratorVariablesTab::slotUpdateLayout()
{
    m_ivariableUIHandler->layout();
}

void CConfiguratorVariablesTab::slotAddVariable()
{
    QString streamname;

    if (!m_ivariableUIHandler->selectStream(streamname) || streamname.isEmpty()) {
        return;
    }
    variableType varType;
    if (!m_ivariableUIHandler->selectVariableType(varType) || (varType == type_unknow)) {
        return;
    }
}

void CConfiguratorVariablesTab::editVariable(const QString &variableName)
{
    CPCWindow::openModal<CEditVariableWindow>(variableName);
}
