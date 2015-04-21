#include "CMaintenanceDiagnosticTab.h"
#include "ui_CMaintenanceDiagnosticTab.h"

CMaintenanceDiagnosticTab::CMaintenanceDiagnosticTab(QWidget *parent)
    : IMaintenanceTab(parent)
    , ui(new Ui::CMaintenanceDiagnosticTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IMaintenanceTab::backTriggered);
}

CMaintenanceDiagnosticTab::~CMaintenanceDiagnosticTab()
{
    delete ui;
}
