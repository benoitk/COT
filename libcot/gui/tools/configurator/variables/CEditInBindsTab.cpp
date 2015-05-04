#include "CEditInBindsTab.h"
#include "ui_CEditInBindsTab.h"

CEditInBindsTab::CEditInBindsTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditInBindsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IEditVariableTab::backTriggered);
}

CEditInBindsTab::~CEditInBindsTab()
{
    delete ui;
}

