#include "CConfiguratorCycleTab.h"
#include "ui_CConfiguratorCycleTab.h"
#include "CConfiguratorCycleTabUIHandler.h"
#include "CEditCycleWindow.h"
#include "CPCWindow.h"

#include <CAutomate.h>
#include <CVariableStream.h>
#include <CCycleFactory.h>

CConfiguratorCycleTab::CConfiguratorCycleTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorCycleTab)
    , m_handler(new CConfiguratorCycleTabUIHandler(0, this))
{
    ui->setupUi(this);
    m_handler->setScrollableWidget(ui->swCentral);
    ui->vbbButtons->addAction(CToolButton::Add);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    slotUpdateLayout();

    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorCycleTab::slotAddCycle);
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered, this, &IConfiguratorTab::signalBackTriggered);
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsUpdated, this, &CConfiguratorCycleTab::slotUpdateLayout);
    connect(CAutomate::getInstance(), &CAutomate::signalCyclesUpdated, this, &CConfiguratorCycleTab::slotUpdateLayout);
}

CConfiguratorCycleTab::~CConfiguratorCycleTab()
{
    delete ui;
}

void CConfiguratorCycleTab::slotAddCycle()
{
    // user can't deny a type
    eTypeCycle cycleType;
    if (!m_handler->selectCycleType(cycleType) || cycleType == CYCLE_INVALID) {
        return;
    }

    // user can deny adding to a stream so it become a global cycle.
    QString streamName;
    m_handler->selectStream(streamName);

    // Create cycle
    ICycle *cycle = CCycleFactory::build(cycleType);
    Q_ASSERT(cycle);
    cycle->setName(QStringLiteral("new_cycle_%1").arg(qrand() %1000));
    cycle->setLbl(tr("New cycle"));
    cycle->setRelatedStreamName(streamName);

    // Edit the new cycle
    CPCWindow::openModal<CEditCycleWindow>(cycle);
}

void CConfiguratorCycleTab::slotUpdateLayout()
{
    m_handler->layout();
}
