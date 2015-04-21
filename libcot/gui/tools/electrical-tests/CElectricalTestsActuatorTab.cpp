#include "CElectricalTestsActuatorTab.h"
#include "ui_CElectricalTestsActuatorTab.h"

CElectricalTestsActuatorTab::CElectricalTestsActuatorTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsActuatorTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTestsActuatorTab::~CElectricalTestsActuatorTab()
{
    delete ui;
}
