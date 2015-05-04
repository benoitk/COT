#include "CEditVariableTab.h"
#include "ui_CEditVariableTab.h"

CEditVariableTab::CEditVariableTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditVariableTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IEditVariableTab::backTriggered);
}

CEditVariableTab::~CEditVariableTab()
{
    delete ui;
}

