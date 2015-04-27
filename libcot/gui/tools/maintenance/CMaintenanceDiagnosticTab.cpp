#include "CMaintenanceDiagnosticTab.h"
#include "ui_CMaintenanceDiagnosticTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CMaintenanceDiagnosticTab::CMaintenanceDiagnosticTab(QWidget *parent)
    : IMaintenanceTab(parent)
    , ui(new Ui::CMaintenanceDiagnosticTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    m_diagnosticHandler = new IVariableUIHandler(ui->swCentral, this);
    slotUpdateLayout();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayChanged,
            this, &CMaintenanceDiagnosticTab::slotUpdateLayout);

    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IMaintenanceTab::backTriggered);
}

CMaintenanceDiagnosticTab::~CMaintenanceDiagnosticTab()
{
    delete ui;
}

void CMaintenanceDiagnosticTab::slotUpdateLayout()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    IVariablePtrList screenDiagnostics = displayConf->getListForScreenDiagnostic();
    m_diagnosticHandler->layout(screenDiagnostics);
}
