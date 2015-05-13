#include "CConfiguratorDisplayTab.h"
#include "ui_CConfiguratorDisplayTab.h"

CConfiguratorDisplayTab::CConfiguratorDisplayTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorDisplayTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::signalBackTriggered);
}

CConfiguratorDisplayTab::~CConfiguratorDisplayTab()
{
    delete ui;
}

