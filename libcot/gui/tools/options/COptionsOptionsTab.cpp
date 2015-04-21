#include "COptionsOptionsTab.h"
#include "ui_COptionsOptionsTab.h"

COptionsOptionsTab::COptionsOptionsTab(QWidget *parent)
    : IOptionsTab(parent)
    , ui(new Ui::COptionsOptionsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IOptionsTab::backTriggered);
}

COptionsOptionsTab::~COptionsOptionsTab()
{
    delete ui;
}
