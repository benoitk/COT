#include "COptionsSchedulerTab.h"
#include "ui_COptionsSchedulerTab.h"

COptionsSchedulerTab::COptionsSchedulerTab(QWidget *parent)
    : IOptionsTab(parent)
    , ui(new Ui::COptionsSchedulerTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IOptionsTab::backTriggered);
}

COptionsSchedulerTab::~COptionsSchedulerTab()
{
    delete ui;
}
