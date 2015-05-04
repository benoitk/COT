#include "CEditOutBindsTab.h"
#include "ui_CEditOutBindsTab.h"

CEditOutBindsTab::CEditOutBindsTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditOutBindsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IEditVariableTab::backTriggered);
}

CEditOutBindsTab::~CEditOutBindsTab()
{
    delete ui;
}

