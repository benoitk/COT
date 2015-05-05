#include "CEditInBindsTab.h"
#include "ui_CEditInBindsTab.h"

#include <ConfiguratorUIHandler.h>

CEditInBindsTab::CEditInBindsTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditInBindsTab)
{
    ui->setupUi(this);
    m_configuratorUIHandler = new ConfiguratorUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IEditVariableTab::backTriggered);
}

CEditInBindsTab::~CEditInBindsTab()
{
    delete ui;
}

