#include "CPCMeasureTab.h"
#include "ui_CPCMeasureTab.h"
#include "IVariableMeasuresUIHandler.h"
#include "CPCWindow.h"
#include "CAlarmsWindow.h"
#include "CDisplayConf.h"
#include "CPlotObject.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"
#include "CDialogConfirmation.h"
#include "ICommand.h"

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
    connect(ui->vbbButtons->addAction(CToolButton::PlayStop), &QAction::triggered,
            this, &CPCMeasureTab::slotPlayStopTriggered);
    ui->vbbButtons->button(CToolButton::PlayStop)->setCheckable(true);
   // connect(ui->vbbButtons->addAction(CToolButton::Stop), &QAction::triggered,
   //         this, &CPCMeasureTab::slotStopTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::StopEndCycle), &QAction::triggered,
            this, &CPCMeasureTab::slotStopEndCycleTriggered);
    ui->vbbButtons->button(CToolButton::StopEndCycle)->setCheckable(true);
    connect(ui->vbbButtons->addAction(CToolButton::NextStream), &QAction::triggered,
            this, &CPCMeasureTab::slotNextStreamTriggered);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsUpdated,
            this, &CPCMeasureTab::slotUpdateStreamsMeasures);
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged,
            this, &CPCMeasureTab::slotVariableChanged);
    connect(m_pendingAlarms, &CPendingAlarms::changed, this, &CPCMeasureTab::updateAlarmsAction);
    connect(CAutomate::getInstance(), &CAutomate::signalUpdateStateAutomate, this, &CPCMeasureTab::slotUpdateControlButtons);
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

void CPCMeasureTab::slotUpdateControlButtons(CAutomate::eStateAutomate arg_state){
    switch(arg_state){
    case CAutomate::RUNNING:
        ui->vbbButtons->button(CToolButton::PlayStop)->setChecked(true);
        ui->vbbButtons->button(CToolButton::StopEndCycle)->setChecked(false);
        break;
    case CAutomate::STOPPED:
        ui->vbbButtons->button(CToolButton::PlayStop)->setChecked(false);
        ui->vbbButtons->button(CToolButton::StopEndCycle)->setChecked(false);
        break;
    case CAutomate::RUNNING_WILL_STOP_END_CYCLE:
        ui->vbbButtons->button(CToolButton::StopEndCycle)->setChecked(true);
        break;
    }
}

void CPCMeasureTab::slotAlarmsTriggered()
{
    CPCWindow::openModal<CAlarmsWindow>(m_pendingAlarms);
}

void CPCMeasureTab::slotPlayStopTriggered()
{
    if(CUserSession::getInstance()->loginUser() )
        CAutomate::getInstance()->getCommandPlayStop()->slotRunCommand();

}

void CPCMeasureTab::slotStopTriggered()
{
    if(CUserSession::getInstance()->loginUser())
        CAutomate::getInstance()->requestStopScheduler();
}

void CPCMeasureTab::slotStopEndCycleTriggered()
{
    if(CUserSession::getInstance()->loginUser())
    {
        if(!ui->vbbButtons->button(CToolButton::StopEndCycle)->isChecked() &&
                CPCWindow::openExec<CDialogConfirmation>(tr("Are you sure ? \nThe measurment will stop after this cycle"),this))
            CAutomate::getInstance()->getCommandStopEndCycle()->slotRunCommand();
        else if(ui->vbbButtons->button(CToolButton::StopEndCycle)->isChecked() &&
                CPCWindow::openExec<CDialogConfirmation>(tr("Cancel stop end cycle ? \n"),this))
            CAutomate::getInstance()->getCommandStopEndCycle()->slotRunCommand();
    }
}

void CPCMeasureTab::slotNextStreamTriggered()
{
    if(CUserSession::getInstance()->loginUser() && CPCWindow::openExec<CDialogConfirmation>(tr("Are you sure ? \nIt will stop the current measurment"),this))
        CAutomate::getInstance()->requestPlayNextSequenceMesure();
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
        ui->swCentral->setScrollable(false); //si scrollable, ne met que deux mesures alors qu'il y a plein de place
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
            ui->graphicsWidget->addPoint(value, plot,measureVar->getMeasureMin()->toFloat(), measureVar->getMeasureMax()->toFloat());
        }
    }
    ui->graphicsWidget->doneUpdatingPlotting();
}
