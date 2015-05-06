#include "CConfiguratorVariablesTab.h"
#include "ui_CConfiguratorVariablesTab.h"
#include "CPCWindow.h"
#include "CEditVariableWindow.h"

#include <ConfiguratorVariablesUIHandler.h>

CConfiguratorVariablesTab::CConfiguratorVariablesTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorVariablesTab)
{
    ui->setupUi(this);
    m_ivariableUIHandler = new ConfiguratorVariablesUIHandler(ui->swCentral, this);
    connect(m_ivariableUIHandler, &ConfiguratorVariablesUIHandler::editVariable, this, &CConfiguratorVariablesTab::editVariable);
    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered,
            this, &CConfiguratorVariablesTab::addVariable);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
}

CConfiguratorVariablesTab::~CConfiguratorVariablesTab()
{
    delete ui;
}

void CConfiguratorVariablesTab::addVariable()
{
    const QString streamname = m_ivariableUIHandler->selectStream();
    if (!streamname.isEmpty()) {
        //TODO add it
    }
}

void CConfiguratorVariablesTab::editVariable(const QString &variableName)
{
    CPCWindow::openModal<CEditvariableWindow>(variableName);
}
