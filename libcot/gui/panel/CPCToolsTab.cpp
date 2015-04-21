#include "CPCToolsTab.h"
#include "ui_CPCToolsTab.h"

CPCToolsTab::CPCToolsTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCToolsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
}

CPCToolsTab::~CPCToolsTab()
{
    delete ui;
}
