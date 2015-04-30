#include "CConfiguratorNetworkTab.h"
#include "ui_CConfiguratorNetworkTab.h"

CConfiguratorNetworkTab::CConfiguratorNetworkTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorNetworkTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
}

CConfiguratorNetworkTab::~CConfiguratorNetworkTab()
{
    delete ui;
}

