#include "CConfiguratorCycleTab.h"
#include "ui_CConfiguratorCycleTab.h"

CConfiguratorCycleTab::CConfiguratorCycleTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorCycleTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
}

CConfiguratorCycleTab::~CConfiguratorCycleTab()
{
    delete ui;
}

