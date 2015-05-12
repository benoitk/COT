#include "CConfiguratorHardwareTab.h"
#include "ui_CConfiguratorHardwareTab.h"

CConfiguratorHardwareTab::CConfiguratorHardwareTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorHardwareTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::signalBackTriggered);
}

CConfiguratorHardwareTab::~CConfiguratorHardwareTab()
{
    delete ui;
}

