#include "CMaintenanceWindow.h"
#include "ui_CMaintenanceWindow.h"
#include "CMaintenanceMaintenanceTab.h"
#include "CMaintenanceDiagnosticTab.h"

CMaintenanceWindow::CMaintenanceWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CMaintenanceWindow)
{
    ui->setupUi(this);
    addTab(new CMaintenanceMaintenanceTab(this), QString());
    addTab(new CMaintenanceDiagnosticTab(this), QString());
    retranslate();
}

CMaintenanceWindow::~CMaintenanceWindow()
{

}

void CMaintenanceWindow::backTriggered()
{
    close();
}

void CMaintenanceWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("MAINTENANCE"));
    ui->twPages->setTabText(1, tr("DIAGNOSTIC"));
}

void CMaintenanceWindow::addTab(IMaintenanceTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IMaintenanceTab::backTriggered, this, &CMaintenanceWindow::backTriggered);
}

void CMaintenanceWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}
