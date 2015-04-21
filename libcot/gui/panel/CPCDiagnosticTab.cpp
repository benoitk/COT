#include "CPCDiagnosticTab.h"
#include "ui_CPCDiagnosticTab.h"

CPCDiagnosticTab::CPCDiagnosticTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCDiagnosticTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
}

CPCDiagnosticTab::~CPCDiagnosticTab()
{
    delete ui;
}
