#include "CElectricalTestsActuatorTab.h"
#include "ui_CElectricalTestsActuatorTab.h"

CElectricalTestsActuatorTab::CElectricalTestsActuatorTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsActuatorTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CVerticalButtonBar::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTestsActuatorTab::~CElectricalTestsActuatorTab()
{
    delete ui;
}
