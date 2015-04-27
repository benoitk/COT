#include "CMaintenanceMaintenanceTab.h"
#include "ui_CMaintenanceMaintenanceTab.h"
#include "IVariableUIHandler.h"
#include "CAutomate.h"

CMaintenanceMaintenanceTab::CMaintenanceMaintenanceTab(QWidget *parent)
    : IMaintenanceTab(parent)
    , ui(new Ui::CMaintenanceMaintenanceTab)
{
    ui->setupUi(this);
    m_variableHandler = new IVariableUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    slotUpdateLayout();

    connect(CAutomate::getInstance(), &CAutomate::signalStreamsChanged,
            this, &CMaintenanceMaintenanceTab::slotUpdateLayout);
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IMaintenanceTab::backTriggered);
}

CMaintenanceMaintenanceTab::~CMaintenanceMaintenanceTab()
{
    delete ui;
}

void CMaintenanceMaintenanceTab::slotUpdateLayout()
{
    CAutomate *automate = CAutomate::getInstance();
    QList<ICycle *> cycles = automate->getListCycles();
    IVariablePtrList variables;

    m_variableHandler->layout(variables);
}
