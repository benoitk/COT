#include "CPCHistogramTab.h"
#include "ui_CPCHistogramTab.h"

CPCHistogramTab::CPCHistogramTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCHistogramTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
}

CPCHistogramTab::~CPCHistogramTab()
{
    delete ui;
}

CVerticalButtonBar *CPCHistogramTab::buttonBar() const
{
    return ui->vbbButtons;
}
