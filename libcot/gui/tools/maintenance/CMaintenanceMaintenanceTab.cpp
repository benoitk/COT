#include "CMaintenanceMaintenanceTab.h"
#include "ui_CMaintenanceMaintenanceTab.h"
#include "IVariableMaintenanceUIHandler.h"
#include "CAutomate.h"
#include "ICycle.h"

CMaintenanceMaintenanceTab::CMaintenanceMaintenanceTab(QWidget *parent)
    : IMaintenanceTab(parent)
    , ui(new Ui::CMaintenanceMaintenanceTab)
{
    ui->setupUi(this);
    m_variableHandler = new IVariableMaintenanceUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    slotUpdateLayout();

    CAutomate *automate = CAutomate::getInstance();

    connect(automate, &CAutomate::signalCyclesChanged, this, &CMaintenanceMaintenanceTab::slotUpdateLayout);
    connect(automate, &CAutomate::signalCurrentMaintenanceCycleChanged, this, &CMaintenanceMaintenanceTab::slotCurrentMaintenanceCycleChanged);
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered, this, &IMaintenanceTab::backTriggered);
}

CMaintenanceMaintenanceTab::~CMaintenanceMaintenanceTab()
{
    delete ui;
}

void CMaintenanceMaintenanceTab::slotUpdateLayout()
{
    m_variableHandler->layout();
}

void CMaintenanceMaintenanceTab::slotCurrentMaintenanceCycleChanged(const QString &name)
{
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(name, CYCLE_MAINTENANCE);

    ui->lStepName->clear();
    ui->lStep->clear();

    if (!cycle) {
        return;
    }

    switch (automate->getStateCycleMaintenance()) {
        case CAutomate::CYCLE_STATE_STOP:
            ui->lStepName->setText(tr("Stopped"));
            break;

        case CAutomate::CYCLE_STATE_RUN:
            ui->lStepName->setText(cycle->getLbl());
            ui->lStep->setNum(cycle->getCurrentStepIndex());
            break;

        case CAutomate::CYCLE_STATE_PAUSE:
            ui->lStepName->setText(tr("Paused"));
            ui->lStep->setNum(cycle->getCurrentStepIndex());
            break;
    }
}
