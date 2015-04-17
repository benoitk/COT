#include "CElectricalTests420Tab.h"
#include "ui_CElectricalTests420Tab.h"

CElectricalTests420Tab::CElectricalTests420Tab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTests420Tab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CVerticalButtonBar::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTests420Tab::~CElectricalTests420Tab()
{
    delete ui;
}
