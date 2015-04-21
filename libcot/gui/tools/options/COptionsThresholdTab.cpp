#include "COptionsThresholdTab.h"
#include "ui_COptionsThresholdTab.h"

COptionsThresholdTab::COptionsThresholdTab(QWidget *parent)
    : IOptionsTab(parent)
    , ui(new Ui::COptionsThresholdTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IOptionsTab::backTriggered);
}

COptionsThresholdTab::~COptionsThresholdTab()
{
    delete ui;
}
