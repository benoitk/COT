#include "CConfiguratorSequencerTab.h"
#include "ConfiguratorSequencerUIHandler.h"
#include "ui_CConfiguratorSequencerTab.h"

CConfiguratorSequencerTab::CConfiguratorSequencerTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorSequencerTab)
{
    ui->setupUi(this);
    m_isequencerUIHandler = new ConfiguratorSequencerUIHandler(ui->swCentral, this);
    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered,
            this, &CConfiguratorSequencerTab::slotAddSequencer);

    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
}

CConfiguratorSequencerTab::~CConfiguratorSequencerTab()
{
    delete ui;
}

void CConfiguratorSequencerTab::slotAddSequencer()
{
    const QString newCycleName = m_isequencerUIHandler->selectCycle();
    if (!newCycleName.isEmpty()) {
        //TODO add new cycle.
    }
}
