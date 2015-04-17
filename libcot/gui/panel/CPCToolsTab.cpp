#include "CPCToolsTab.h"
#include "ui_CPCToolsTab.h"

CPCToolsTab::CPCToolsTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCToolsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
}

CPCToolsTab::~CPCToolsTab()
{
    delete ui;
}
