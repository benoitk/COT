#include "CElectricalTestsInputsTab.h"
#include "ui_CElectricalTestsInputsTab.h"

CElectricalTestsInputsTab::CElectricalTestsInputsTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsInputsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTestsInputsTab::~CElectricalTestsInputsTab()
{
    delete ui;
}
