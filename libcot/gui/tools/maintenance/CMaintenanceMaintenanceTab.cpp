#include "CMaintenanceMaintenanceTab.h"
#include "ui_CMaintenanceMaintenanceTab.h"

CMaintenanceMaintenanceTab::CMaintenanceMaintenanceTab(QWidget *parent)
    : IMaintenanceTab(parent)
    , ui(new Ui::CMaintenanceMaintenanceTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IMaintenanceTab::backTriggered);
}

CMaintenanceMaintenanceTab::~CMaintenanceMaintenanceTab()
{
    delete ui;
}
