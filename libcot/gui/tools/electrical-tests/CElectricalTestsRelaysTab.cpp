#include "CElectricalTestsRelaysTab.h"
#include "ui_CElectricalTestsRelaysTab.h"

CElectricalTestsRelaysTab::CElectricalTestsRelaysTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsRelaysTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTestsRelaysTab::~CElectricalTestsRelaysTab()
{
    delete ui;
}
