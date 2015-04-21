#include "CPCMeasureTab.h"
#include "ui_CPCMeasureTab.h"

CPCMeasureTab::CPCMeasureTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCMeasureTab)
{
    ui->setupUi(this);

    connect(ui->vbbButtons->addAction(CToolButton::Alarms), &QAction::triggered,
            this, &CPCMeasureTab::alarmsTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Play), &QAction::triggered,
            this, &CPCMeasureTab::playTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Stop), &QAction::triggered,
            this, &CPCMeasureTab::stopTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::StopEndCycle), &QAction::triggered,
            this, &CPCMeasureTab::stopEndCycleTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::NextStream), &QAction::triggered,
            this, &CPCMeasureTab::nextStreamTriggered);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
}

CPCMeasureTab::~CPCMeasureTab()
{
    delete ui;
}

void CPCMeasureTab::alarmsTriggered()
{

}

void CPCMeasureTab::playTriggered()
{

}

void CPCMeasureTab::stopTriggered()
{

}

void CPCMeasureTab::stopEndCycleTriggered()
{

}

void CPCMeasureTab::nextStreamTriggered()
{

}
