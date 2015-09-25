#include "CStatusWidget.h"
#include "ui_CStatusWidget.h"
#include <QDateTime>
#include <QTimer>

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
    connect(automate, &CAutomate::signalUpdateCountStep,
            this, &CStatusWidget::slotUpdateCountStep);
    connect(automate, &CAutomate::signalUpdateCurrentAction,
            this, &CStatusWidget::slotUpdateCurrentAction);
    connect(automate, &CAutomate::signalNewAlarm,
            this, &CStatusWidget::slotAddAlarm);
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
     ui->lCycle->setStyleSheet("QLabel { color : black; }");
    switch (state) {
    case CAutomate::RUNNING:
        text = tr("CYCLE IN PROGRESS");
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

    ui->lCycle->setText(text);

}
void CStatusWidget::slotAddAlarm(const QString& arg_default){
    ui->lCycle->setStyleSheet("QLabel { color : red; }");
    ui->lCycle->setText(ui->lCycle->text() + " / " + arg_default);
}
void CStatusWidget::slotCleanDefaults(){
    ui->lCycle->setStyleSheet("QLabel { color : black; }");
    QString tmp = ui->lCycle->text();
    ui->lCycle->setText(tmp.split("/").value(0));
}

void CStatusWidget::slotUpdateCurrentStream(int stream, const QString &label)
{
    Q_UNUSED(stream); // the user doesn't care for the stream number, right?
    ui->lStream->setText(label);
}

void CStatusWidget::slotUpdateCurrentStep(float step, const QString &label)
{
    m_lblInfoStep = label;
    ui->lCurrentStep->setText(QString("Step: %1").arg(step));
    ui->lLabel->setText(label);
}

 void CStatusWidget::slotUpdateCurrentAction(const QString &label)
 {
     ui->lLabel->setText(m_lblInfoStep + " : " + label);
 }
void CStatusWidget::slotUpdateCountStep(int stepCount)
{
    ui->lTotalStep->setText(QString("On: %1").arg(stepCount));
}
