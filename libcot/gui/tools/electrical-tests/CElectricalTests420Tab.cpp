#include "CElectricalTests420Tab.h"
#include "ui_CElectricalTests420Tab.h"

CElectricalTests420Tab::CElectricalTests420Tab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTests420Tab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTests420Tab::~CElectricalTests420Tab()
{
    delete ui;
}
