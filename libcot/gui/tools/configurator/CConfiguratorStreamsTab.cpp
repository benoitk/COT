#include "CConfiguratorStreamsTab.h"
#include "ui_CConfiguratorStreamsTab.h"

CConfiguratorStreamsTab::CConfiguratorStreamsTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorStreamsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
}

CConfiguratorStreamsTab::~CConfiguratorStreamsTab()
{
    delete ui;
}

