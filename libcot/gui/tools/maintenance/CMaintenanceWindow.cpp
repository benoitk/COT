#include "CMaintenanceWindow.h"
#include "ui_CMaintenanceWindow.h"
#include "CMaintenanceMaintenanceTab.h"
#include "CMaintenanceDiagnosticTab.h"

CMaintenanceWindow::CMaintenanceWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CMaintenanceWindow)
{
    ui->setupUi(this);
    addTab(new CMaintenanceMaintenanceTab(this), tr("MAINTENANCE"));
    addTab(new CMaintenanceDiagnosticTab(this), tr("DIAGNOSTIC"));
}

CMaintenanceWindow::~CMaintenanceWindow()
{

}

void CMaintenanceWindow::backTriggered()
{
    close();
}

void CMaintenanceWindow::addTab(IMaintenanceTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IMaintenanceTab::backTriggered, this, &CMaintenanceWindow::backTriggered);
}
