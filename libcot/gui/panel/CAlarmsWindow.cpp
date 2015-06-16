#include "CAlarmsWindow.h"
#include "ui_CAlarmsWindow.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

#include <QLabel>
#include <QDebug>
#include <QScrollBar>

/// Backend class

void CPendingAlarms::addAlarm(int id, const QDateTime &dateTime, const QString &description)
{
    for (size_t i = 0 ; i < m_alarms.size() ; ++i) {
        if (m_alarms.at(i).id == id)
            return; // already having a pending alarm for this id
    }
    m_alarms.push_back(Alarm(id, dateTime, description));
    emit changed();
}

void CPendingAlarms::clearAlarms()
{
    m_alarms.clear();
    emit changed();
}

QString CPendingAlarms::alarmsFormattedText() const
{
    QString text;
    for (size_t i = 0 ; i < m_alarms.size() ; ++i) {
        const Alarm &alarm = m_alarms.at(i);
        text += tr("%1: %2").arg(alarm.dateTime.toString(), alarm.description) + '\n';
    }
    return text;
}


/// GUI

CAlarmsWindow::CAlarmsWindow(CPendingAlarms *alarms, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CAlarmsWindow)
    , m_pendingAlarms(alarms)
{
    ui->setupUi(this);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &CAlarmsWindow::slotRemoveAlarms);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->pteHistory->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->pteHistory->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &CAlarmsWindow::backTriggered);
    connect(alarms, &CPendingAlarms::changed, this, &CAlarmsWindow::slotAlarmsChanged);
    slotAlarmsChanged();
}

CAlarmsWindow::~CAlarmsWindow()
{
    delete ui;
}

void CAlarmsWindow::backTriggered()
{
    close();
}

void CAlarmsWindow::slotAlarmsChanged()
{
    const QString text = m_pendingAlarms->alarmsFormattedText();
    ui->pteHistory->setPlainText(text);
    ui->pteHistory->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
}

void CAlarmsWindow::slotRemoveAlarms()
{
    m_pendingAlarms->clearAlarms();
}
