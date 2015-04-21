#include "CMeasureMeasureTab.h"
#include "ui_CMeasureMeasureTab.h"

CMeasureMeasureTab::CMeasureMeasureTab(QWidget *parent) :
    IMeasureTab(parent),
    ui(new Ui::CMeasureMeasureTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IMeasureTab::backTriggered);
}

CMeasureMeasureTab::~CMeasureMeasureTab()
{
    delete ui;
}
