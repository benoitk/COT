#include "COptionsAutoCyclesTab.h"
#include "ui_COptionsAutoCyclesTab.h"

COptionsAutoCyclesTab::COptionsAutoCyclesTab(QWidget *parent)
    : IOptionsTab(parent)
    , ui(new Ui::COptionsAutoCyclesTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IOptionsTab::backTriggered);
}

COptionsAutoCyclesTab::~COptionsAutoCyclesTab()
{
    delete ui;
}
