#include "CPCMeasureTab.h"
#include "ui_CPCMeasureTab.h"
#include "IVariableMeasuresUIHandler.h"
#include "CAutomate.h"

CPCMeasureTab::CPCMeasureTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCMeasureTab)
{
    ui->setupUi(this);
    m_measuresHandler =new IVariableMeasuresUIHandler(ui->swCentral, this);
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
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsMeasuresChanged,
            this, &CPCMeasureTab::slotUpdateStreamsMeasures);
}

CPCMeasureTab::~CPCMeasureTab()
{
    delete ui;
}

void CPCMeasureTab::slotAlarmsTriggered()
{

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
    QMap<QString, QList<QString>> streams = automate->getMapStreamsMeasures();
    QStringList variables;

    // KDAB: Remove me once customer api is ready
    if (streams.isEmpty()) {
        // create vars in automate
        automate->getStreams();
        automate->getStreamVariables("");
        automate->getStreamMeasures("");

        // fake list
        streams["stream_1"] << "measure_silice" << "measure_silice_2";
        streams["stream_2"] << "measure_silice_3" << "measure_silice_4";
    }

    variables << streams.value("stream_1");
    variables << streams.value("stream_2");
    m_measuresHandler->layout(variables);
}
