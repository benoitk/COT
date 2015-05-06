#include "CConfiguratorSequencerTab.h"
#include "ConfiguratorSequencerUIHandler.h"
#include "ui_CConfiguratorSequencerTab.h"

CConfiguratorSequencerTab::CConfiguratorSequencerTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorSequencerTab)
{
    ui->setupUi(this);
    m_isequencerUIHandler = new ConfiguratorSequencerUIHandler(ui->swCentral, this);

    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
}

CConfiguratorSequencerTab::~CConfiguratorSequencerTab()
{
    delete ui;
}

