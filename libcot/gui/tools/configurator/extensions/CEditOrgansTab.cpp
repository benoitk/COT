#include "CEditOrgansTab.h"
#include "ui_CEditOrgansTab.h"
#include "CAutomate.h"

CEditOrgansTab::CEditOrgansTab(QWidget *parent)
    : IEditExtensionTab(parent)
    , ui(new Ui::CEditOrgansTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IEditExtensionTab::backTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &IEditExtensionTab::okTriggered);
}

CEditOrgansTab::~CEditOrgansTab()
{
    delete ui;
}
