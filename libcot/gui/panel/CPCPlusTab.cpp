#include "CPCPlusTab.h"
#include "ui_CPCPlusTab.h"

CPCPlusTab::CPCPlusTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCPlusTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
}

CPCPlusTab::~CPCPlusTab()
{
    delete ui;
}
