#include "CElectricalTestsInputsTab.h"
#include "ui_CElectricalTestsInputsTab.h"

CElectricalTestsInputsTab::CElectricalTestsInputsTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsInputsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CVerticalButtonBar::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTestsInputsTab::~CElectricalTestsInputsTab()
{
    delete ui;
}
