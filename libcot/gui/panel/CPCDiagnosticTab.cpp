#include "CPCDiagnosticTab.h"
#include "ui_CPCDiagnosticTab.h"

CPCDiagnosticTab::CPCDiagnosticTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCDiagnosticTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CVerticalButtonBar::ScrollDown, ui->swCentral->moveDown());
}

CPCDiagnosticTab::~CPCDiagnosticTab()
{
    delete ui;
}
