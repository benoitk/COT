#include "CStatusWidget.h"
#include "ui_CStatusWidget.h"
#include "CScheduler.h"

#include <QDateTime>
#include <QTimer>
#include <qdebug.h>

#define SEPARATOR_MEASURE_ALARM " / "

CStatusWidget::CStatusWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CStatusWidget)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CStatusWidget::slotTimeChanged);
    timer->start(1);

    CAutomate *automate = CAutomate::getInstance();
    connect(automate, &CAutomate::signalUpdateStateAutomate,
            this, &CStatusWidget::slotUpdateStateAutomate);
    connect(automate, &CAutomate::signalUpdateCurrentStream,
            this, &CStatusWidget::slotUpdateCurrentStream);
    connect(automate, &CAutomate::signalUpdateCurrentStep,
            this, &CStatusWidget::slotUpdateCurrentStep);
    connect(automate, &CAutomate::signalUpdateNumStep,
            this, &CStatusWidget::slotUpdateNumStep);
    connect(automate, &CAutomate::signalUpdateCountStep,
            this, &CStatusWidget::slotUpdateCountStep);
    connect(automate, &CAutomate::signalUpdateCurrentAction,
            this, &CStatusWidget::slotUpdateCurrentAction);
    connect(automate, &CAutomate::signalNewAlarm,
            this, &CStatusWidget::slotAddAlarm);
    connect(automate, &CAutomate::signalRemoveAlarm,
            this, &CStatusWidget::slotRemoveAlarm);

}

CStatusWidget::~CStatusWidget()
{
    delete ui;
}

void CStatusWidget::slotTimeChanged()
{
    const QDateTime now = QDateTime::currentDateTime();
    ui->lDateTime->setText(now.toString());
}

void CStatusWidget::slotUpdateStateAutomate(CAutomate::eStateAutomate state)
{
    QString text;
    QString oldText = ui->lCycle->text();
    switch (state) {
    case CAutomate::RUNNING:
        text = tr("CYCLE IN PROGRESS : ") + CScheduler::getInstance()->getCycleInProgressName() + "\n";
        break;
    case CAutomate::PAUSED:
        text = tr("PAUSED");
        break;
    case CAutomate::CALIBRATION:
        text = tr("CALIBRATION");
        break;
    case CAutomate::WAITING:
        text = tr("WAITING");
        break;
    case CAutomate::STOPPED:
        text = tr("STOPPED");
        break;
    }

    if(oldText.contains(SEPARATOR_MEASURE_ALARM)){
        QStringList listTmp = oldText.split(SEPARATOR_MEASURE_ALARM);
        for(int i=1; i < listTmp.count(); ++i) text += QString(SEPARATOR_MEASURE_ALARM) +listTmp.at(i);
    }
    else{
        ui->lCycle->setStyleSheet("QLabel { color : black; }");
    }

    ui->lCycle->setText(text);

}
void CStatusWidget::slotAddAlarm(const QString& arg_default){
    ui->lCycle->setStyleSheet("QLabel { color : red; }");
    if(!ui->lCycle->text().contains(arg_default))
        ui->lCycle->setText(ui->lCycle->text() + SEPARATOR_MEASURE_ALARM + arg_default);
}
void CStatusWidget::slotRemoveAlarm(const QString& arg_default){

    QStringList list = ui->lCycle->text().split(SEPARATOR_MEASURE_ALARM);
    QString tmp = list.takeFirst();
    if(list.count()<2)
        ui->lCycle->setStyleSheet("QLabel { color : black; }");
    foreach (const QString& s, list) {
        qDebug() << s << "&&"<< arg_default << "&&";
        if(s != arg_default)
            tmp += SEPARATOR_MEASURE_ALARM + s;
    }
    ui->lCycle->setText(tmp);
}
void CStatusWidget::slotCleanDefaults(){
    ui->lCycle->setStyleSheet("QLabel { color : black; }");
    QString tmp = ui->lCycle->text();
    ui->lCycle->setText(tmp.split(SEPARATOR_MEASURE_ALARM).value(0));
}

void CStatusWidget::slotUpdateCurrentStream(int stream, const QString &label)
{
    Q_UNUSED(stream); // the user doesn't care for the stream number, right?
    ui->lStream->setText(label);
}

void CStatusWidget::slotUpdateCurrentStep(float step, const QString &label)
{
    if(step>m_stepCount)
        ui->lCurrentStep->setStyleSheet("QLabel { color : red; }");
    else
        ui->lCurrentStep->setStyleSheet("QLabel { color : white; }");

    m_lblInfoStep = label;
    ui->lCurrentStep->setText(QString("Step: ")+ QString::number(step, 'f', 1));
    ui->lLabel->setText(label);
}
void CStatusWidget::slotUpdateNumStep(float step){
    if(step>m_stepCount)
        ui->lCurrentStep->setStyleSheet("QLabel { color : red; }");
    else
        ui->lCurrentStep->setStyleSheet("QLabel { color : white; }");

    ui->lCurrentStep->setText(QString("Step: ")+ QString::number(step, 'f', 1));
}
 void CStatusWidget::slotUpdateCurrentAction(const QString &label)
 {
     ui->lLabel->setText(m_lblInfoStep + " : " + label);
 }
void CStatusWidget::slotUpdateCountStep(int stepCount)
{
    m_stepCount = stepCount;
    ui->lTotalStep->setText(QString("On: %1").arg(stepCount));
}
