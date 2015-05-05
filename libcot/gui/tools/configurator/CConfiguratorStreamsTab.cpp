#include "CConfiguratorStreamsTab.h"
#include "ui_CConfiguratorStreamsTab.h"

#include <IVariableUIHandler.h>

CConfiguratorStreamsTab::CConfiguratorStreamsTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorStreamsTab)
{
    ui->setupUi(this);
    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered,
            this, &CConfiguratorStreamsTab::addVariable);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
    m_ivariableUIHandler = new IVariableUIHandler(ui->swCentral, this);
}

CConfiguratorStreamsTab::~CConfiguratorStreamsTab()
{
    delete ui;
}

void CConfiguratorStreamsTab::addVariable()
{

}
