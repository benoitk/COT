#include "CConfiguratorStreamsTab.h"
#include "ConfiguratorStreamsUIHandler.h"
#include "ui_CConfiguratorStreamsTab.h"

#include <IVariableUIHandler.h>

CConfiguratorStreamsTab::CConfiguratorStreamsTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorStreamsTab)
{
    ui->setupUi(this);
    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered,
            this, &CConfiguratorStreamsTab::slotAddStreams);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::signalBackTriggered);
    m_istreamUIHandler = new ConfiguratorStreamsUIHandler(ui->swCentral, this);
    m_istreamUIHandler->layout();
}

CConfiguratorStreamsTab::~CConfiguratorStreamsTab()
{
    delete ui;
}

void CConfiguratorStreamsTab::slotAddStreams()
{
}
