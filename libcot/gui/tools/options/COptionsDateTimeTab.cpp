#include "COptionsDateTimeTab.h"
#include "ui_COptionsDateTimeTab.h"

COptionsDateTimeTab::COptionsDateTimeTab(QWidget *parent)
    : IOptionsTab(parent)
    , ui(new Ui::COptionsDateTimeTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IOptionsTab::backTriggered);
}

COptionsDateTimeTab::~COptionsDateTimeTab()
{
    delete ui;
}
