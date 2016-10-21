#include "CMaintenanceDiagnosticTab.h"
#include "ui_CMaintenanceDiagnosticTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"


CMaintenanceDiagnosticTab::CMaintenanceDiagnosticTab(CAutomate* arg_automate, QWidget *parent)
    : IMaintenanceTab(parent)
    , ui(new Ui::CMaintenanceDiagnosticTab)
    , m_automate(arg_automate)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    m_diagnosticHandler = new IVariableUIHandler(arg_automate, ui->swCentral, this);
    slotUpdateLayout();
    connect(m_automate, &CAutomate::signalDisplayUpdated,
            this, &CMaintenanceDiagnosticTab::slotUpdateLayout);

}

CMaintenanceDiagnosticTab::~CMaintenanceDiagnosticTab()
{
    delete ui;
}

void CMaintenanceDiagnosticTab::slotUpdateLayout()
{
    CDisplayConf *displayConf = m_automate->getDisplayConf();
    IVariablePtrList screenDiagnostics = displayConf->getListForScreenDiagnostic();
    m_diagnosticHandler->layout(screenDiagnostics);
}
