#include "CPCMeasureTab.h"
#include "ui_CPCMeasureTab.h"
#include "IVariableMeasuresUIHandler.h"
#include "CAutomate.h"
#include "CPCWindow.h"
#include "CAlarmsWindow.h"
#include "CDisplayConf.h"
#include "CPlotObject.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"
#include <QDebug>

CPCMeasureTab::CPCMeasureTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCMeasureTab)
    , m_pendingAlarms(new CPendingAlarms(this))
{
    ui->setupUi(this);
    IVariableMeasuresUIHandler::Flags flags = IVariableMeasuresUIHandler::ShowStreamButton;
    m_measuresHandler = new IVariableMeasuresUIHandler(flags, ui->swCentral, this);

    connect(ui->vbbButtons->addAction(CToolButton::Alarms), &QAction::triggered,
            this, &CPCMeasureTab::slotAlarmsTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Play), &QAction::triggered,
            this, &CPCMeasureTab::slotPlayTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Stop), &QAction::triggered,
            this, &CPCMeasureTab::slotStopTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::StopEndCycle), &QAction::triggered,
            this, &CPCMeasureTab::slotStopEndCycleTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::NextStream), &QAction::triggered,
            this, &CPCMeasureTab::slotNextStreamTriggered);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsUpdated,
            this, &CPCMeasureTab::slotUpdateStreamsMeasures);
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged,
            this, &CPCMeasureTab::slotVariableChanged);
    connect(m_pendingAlarms, &CPendingAlarms::changed, this, &CPCMeasureTab::updateAlarmsAction);

    updateAlarmsAction();
    slotUpdateStreamsMeasures();
}

CPCMeasureTab::~CPCMeasureTab()
{
    delete ui;
}

CVerticalButtonBar *CPCMeasureTab::buttonBar() const
{
    return ui->vbbButtons;
}

void CPCMeasureTab::slotAlarmsTriggered()
{
    CPCWindow::openModal<CAlarmsWindow>(m_pendingAlarms);
}

void CPCMeasureTab::slotPlayTriggered()
{
    CAutomate::getInstance()->playScheduler();
}

void CPCMeasureTab::slotStopTriggered()
{

    CAutomate::getInstance()->stopScheduler();
}

void CPCMeasureTab::slotStopEndCycleTriggered()
{

}

void CPCMeasureTab::slotNextStreamTriggered()
{

}

void CPCMeasureTab::slotUpdateStreamsMeasures()
{
    CAutomate *automate = CAutomate::getInstance();
    const QList<CVariableStream*> streams = automate->getListStreams();
    IVariablePtrList ivars;

    foreach (CVariableStream *streamVar, streams) {

        foreach (IVariable *measure, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);
            ivars << measureVar->getMeasureVariable();
        }
    }

    m_measuresHandler->layout(ivars);

    if (CPCWindow::showGraphInMainScreen()) {
        connect(CAutomate::getInstance(), &CAutomate::signalUpdatePlotting,
                this, &CPCMeasureTab::slotUpdatePlotting, Qt::UniqueConnection);
        ui->swCentral->setScrollable(false);
        ui->graphicsWidget->show();
    }
    else {
        disconnect(CAutomate::getInstance(), &CAutomate::signalUpdatePlotting,
                this, &CPCMeasureTab::slotUpdatePlotting);
        ui->swCentral->setScrollable(true);
        ui->graphicsWidget->hide();
    }
}

void CPCMeasureTab::slotVariableChanged(const QString &name, const QDateTime &dateTime)
{
    CAutomate *automate = CAutomate::getInstance();
    IVariable *ivar = automate->getVariable(name);
    if (!automate->getDisplayConf()->getListForScreenAlarms().contains(ivar)) {
        return;
    }

    if (ivar->toBool()) {
        // will emit changed, which will call updateAlarmsAction
        m_pendingAlarms->addAlarm(name, dateTime, ivar->getLabel());
    }
}

void CPCMeasureTab::updateAlarmsAction()
{
    QAction *action = ui->vbbButtons->action(CToolButton::Alarms);
    action->setIcon(!m_pendingAlarms->isEmpty()
                    ? CToolButton::buttonIcon(CToolButton::AlarmsActive)
                    : CToolButton::buttonIcon(CToolButton::Alarms));
}

void CPCMeasureTab::slotUpdatePlotting()
{
    CAutomate *automate = CAutomate::getInstance();
    const QList<CVariableStream*> streams = automate->getListStreams();
    foreach (CVariableStream *streamVar, streams) {
        foreach (IVariable *measure, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);
            const float value = measureVar->toFloat();
            CPlotObject *plot = m_plotObjectHash.value(measureVar->getName());
            if (!plot) {
                plot = new CPlotObject(measureVar->color());
                m_plotObjectHash.insert(measureVar->getName(), plot);
                ui->graphicsWidget->showPlotObject(plot);
            }
            ui->graphicsWidget->addPoint(value, plot);
        }
    }
    ui->graphicsWidget->doneUpdatingPlotting();
}
