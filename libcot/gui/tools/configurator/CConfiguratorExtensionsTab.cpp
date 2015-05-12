#include "CConfiguratorExtensionsTab.h"
#include "ui_CConfiguratorExtensionsTab.h"

CConfiguratorExtensionsTab::CConfiguratorExtensionsTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorExtensionsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::signalBackTriggered);
}

CConfiguratorExtensionsTab::~CConfiguratorExtensionsTab()
{
    delete ui;
}

