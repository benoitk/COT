#include "CPCPlusTab.h"
#include "ui_CPCPlusTab.h"

CPCPlusTab::CPCPlusTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCPlusTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
}

CPCPlusTab::~CPCPlusTab()
{
    delete ui;
}
