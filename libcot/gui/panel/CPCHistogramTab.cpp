#include "CPCHistogramTab.h"
#include "ui_CPCHistogramTab.h"

CPCHistogramTab::CPCHistogramTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCHistogramTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
}

CPCHistogramTab::~CPCHistogramTab()
{
    delete ui;
}
