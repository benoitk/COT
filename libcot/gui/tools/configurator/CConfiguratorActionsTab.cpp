#include "CConfiguratorActionsTab.h"
#include "ConfiguratorActionsUIHandler.h"
#include "ui_CConfiguratorActionsTab.h"

CConfiguratorActionsTab::CConfiguratorActionsTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorActionsTab)
{
    ui->setupUi(this);
    m_iactionUIHandler = new ConfiguratorActionsUIHandler(ui->swCentral, this);
    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered,
            this, &CConfiguratorActionsTab::addAction);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
}

CConfiguratorActionsTab::~CConfiguratorActionsTab()
{
    delete ui;
}

void CConfiguratorActionsTab::addAction()
{

}

