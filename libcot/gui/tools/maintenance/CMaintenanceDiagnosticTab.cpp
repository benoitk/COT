#include "CMaintenanceDiagnosticTab.h"
#include "ui_CMaintenanceDiagnosticTab.h"
#include "IVariableUIHandler.h"
#include "CAutomate.h"

CMaintenanceDiagnosticTab::CMaintenanceDiagnosticTab(QWidget *parent)
    : IMaintenanceTab(parent)
    , ui(new Ui::CMaintenanceDiagnosticTab)
{
    ui->setupUi(this);
    m_variableHandler = new IVariableUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    slotUpdateLayout();

    connect(CAutomate::getInstance(), &CAutomate::signalStreamsChanged,
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
    QList<ICycle *> cycles = automate->getListCycles();
    IVariablePtrList variables;

    m_variableHandler->layout(variables);
}
