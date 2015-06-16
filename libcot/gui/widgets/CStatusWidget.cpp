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
    ui->lCycle->setText(state == CAutomate::GENERAL_DEFAULT ? QString() : tr("CYCLE IN PROGRESS"));
}

void CStatusWidget::slotUpdateCurrentStream(int stream, const QString &label)
{
    Q_UNUSED(stream); // the user doesn't care for the stream number, right?
    ui->lStream->setText(label);
}

void CStatusWidget::slotUpdateCurrentStep(float step, const QString &label)
{
    ui->lCurrentStep->setText(QString("Step: %1").arg(step));
    ui->lLabel->setText(label);
}

