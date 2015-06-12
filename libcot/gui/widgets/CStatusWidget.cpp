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
