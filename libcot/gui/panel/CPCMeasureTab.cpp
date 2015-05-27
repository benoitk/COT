#include "CPCMeasureTab.h"
#include "ui_CPCMeasureTab.h"
#include "IVariableMeasuresUIHandler.h"
#include "CAutomate.h"
#include "CPCWindow.h"
#include "CAlarmsWindow.h"
#include "CDisplayConf.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"

CPCMeasureTab::CPCMeasureTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCMeasureTab)
{
    ui->setupUi(this);
    m_measuresHandler = new IVariableMeasuresUIHandler(ui->swCentral, this);
    slotUpdateStreamsMeasures();

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
    CPCWindow::openModal<CAlarmsWindow>();
}

void CPCMeasureTab::slotPlayTriggered()
{

}

void CPCMeasureTab::slotStopTriggered()
{

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
}

void CPCMeasureTab::slotVariableChanged(const QString &name)
{
    slotUpdateAlarmsIcon(name);
    slotUpdatePlotting(name);
}

void CPCMeasureTab::slotUpdateAlarmsIcon(const QString &name)
{
    CAutomate *automate = CAutomate::getInstance();
    IVariablePtrList ivars = automate->getDisplayConf()->getListForScreenAlarms();
    IVariable *var = automate->getVariable(name);
    bool alarmActive = false;

    if (ivars.contains(var)) {
        foreach (IVariable *ivar, ivars) {
            if (ivar->toBool()) {
                alarmActive = true;
            }
        }

        QAction *action = ui->vbbButtons->action(CToolButton::Alarms);
        action->setIcon(alarmActive
                        ? CToolButton::buttonIcon(CToolButton::AlarmsActive)
                        : CToolButton::buttonIcon(CToolButton::Alarms));
    }
}

void CPCMeasureTab::slotUpdatePlotting(const QString &name)
{
    CAutomate *automate = CAutomate::getInstance();
    IVariable *var = automate->getVariable(name);
    if (var->isMeasureRelated()) {
        if (var->getType() == type_float) {
            const float value = var->toFloat();
            ui->graphicsWidget->addOrUpdateCurve(value, name);
        }
    }
}
