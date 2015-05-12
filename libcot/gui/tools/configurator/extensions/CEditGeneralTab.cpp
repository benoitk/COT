#include "CEditGeneralTab.h"
#include "ui_CEditGeneralTab.h"
#include "CAutomate.h"

CEditGeneralTab::CEditGeneralTab(QWidget *parent)
    : IEditExtensionTab(parent)
    , ui(new Ui::CEditGeneralTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IEditExtensionTab::backTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &IEditExtensionTab::okTriggered);
}

CEditGeneralTab::~CEditGeneralTab()
{
    delete ui;
}
