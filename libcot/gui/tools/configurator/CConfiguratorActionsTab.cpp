#include "CConfiguratorActionsTab.h"
#include "ui_CConfiguratorActionsTab.h"

CConfiguratorActionsTab::CConfiguratorActionsTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorActionsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
}

CConfiguratorActionsTab::~CConfiguratorActionsTab()
{
    delete ui;
}

