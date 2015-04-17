#include "CElectricalTestsPumpsTab.h"
#include "ui_CElectricalTestsPumpsTab.h"

CElectricalTestsPumpsTab::CElectricalTestsPumpsTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsPumpsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CVerticalButtonBar::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTestsPumpsTab::~CElectricalTestsPumpsTab()
{
    delete ui;
}
