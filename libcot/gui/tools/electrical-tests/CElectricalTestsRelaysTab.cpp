#include "CElectricalTestsRelaysTab.h"
#include "ui_CElectricalTestsRelaysTab.h"

CElectricalTestsRelaysTab::CElectricalTestsRelaysTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsRelaysTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CVerticalButtonBar::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);
}

CElectricalTestsRelaysTab::~CElectricalTestsRelaysTab()
{
    delete ui;
}
