#include "CConfiguratorSequencerTab.h"
#include "ConfiguratorSequencerUIHandler.h"
#include "ui_CConfiguratorSequencerTab.h"

CConfiguratorSequencerTab::CConfiguratorSequencerTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorSequencerTab)
{
    ui->setupUi(this);
    m_isequencerUIHandler = new ConfiguratorSequencerUIHandler(ui->swCentral, this);
    m_isequencerUIHandler->layout();
    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered,
            this, &CConfiguratorSequencerTab::slotAddSequencer);

    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::signalBackTriggered);
}

CConfiguratorSequencerTab::~CConfiguratorSequencerTab()
{
    delete ui;
}

void CConfiguratorSequencerTab::slotAddSequencer()
{
    QString newCycleName;

    if (m_isequencerUIHandler->selectCycle(newCycleName) && !newCycleName.isEmpty()) {
        //TODO add new cycle.
    }
}
