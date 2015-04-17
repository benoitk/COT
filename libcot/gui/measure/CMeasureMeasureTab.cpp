#include "CMeasureMeasureTab.h"
#include "ui_CMeasureMeasureTab.h"

CMeasureMeasureTab::CMeasureMeasureTab(QWidget *parent) :
    IMeasureTab(parent),
    ui(new Ui::CMeasureMeasureTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CVerticalButtonBar::Back), &QAction::triggered,
            this, &IMeasureTab::backTriggered);
}

CMeasureMeasureTab::~CMeasureMeasureTab()
{
    delete ui;
}
