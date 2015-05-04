#include "CConfiguratorVariablesTab.h"
#include "ui_CConfiguratorVariablesTab.h"

#include <IVariableUIHandler.h>

CConfiguratorVariablesTab::CConfiguratorVariablesTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorVariablesTab)
{
    ui->setupUi(this);
    connect(ui->vbbButtons->addAction(CToolButton::AddVariable), &QAction::triggered,
            this, &CConfiguratorVariablesTab::addVariable);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
    m_ivariableUIHandler = new IVariableUIHandler(ui->swCentral, this);
}

CConfiguratorVariablesTab::~CConfiguratorVariablesTab()
{
    delete ui;
}

void CConfiguratorVariablesTab::addVariable()
{
    //TODO
}
