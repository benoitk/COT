#include "CMeasureStreamTab.h"
#include "ui_CMeasureStreamTab.h"

CMeasureStreamTab::CMeasureStreamTab(QWidget *parent) :
    IMeasureTab(parent),
    ui(new Ui::CMeasureStreamTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CVerticalButtonBar::Back), &QAction::triggered,
            this, &IMeasureTab::backTriggered);
}

CMeasureStreamTab::~CMeasureStreamTab()
{
    delete ui;
}
