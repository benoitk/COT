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
    eTypeCycle cycleType;

    if (!m_handler->selectCycleType(cycleType) || cycleType == CYCLE_INVALID) {
        return;
    }

    QString streamName;

    if (!m_handler->selectStream(streamName) || streamName.isEmpty()) {
        return;
    }

    CAutomate *automate = CAutomate::getInstance();
    CVariableStream *stream = static_cast<CVariableStream *>(automate->getMapStreams().value(streamName));
    ICycle *cycle = CCycleFactory::build(cycleType);

    Q_ASSERT(stream);
    Q_ASSERT(cycle);

    cycle->setName("new_cycle");
    cycle->setLbl(tr("New cycle"));

    CPCWindow::openModal<CEditCycleWindow>(CyclePair(streamName, cycle));
}

void CConfiguratorCycleTab::slotUpdateLayout()
{
    m_handler->layout();
}
