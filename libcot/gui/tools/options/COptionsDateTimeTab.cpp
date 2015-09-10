#include "COptionsDateTimeTab.h"
#include "ui_COptionsDateTimeTab.h"
#include <cotgui_debug.h>

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <CNumericalKeyboardDialog.h>
#include <QProcess>

#include <cerrno>

#ifdef Q_OS_UNIX
#include <time.h>
#endif

#if defined(Q_OS_MAC)
#include <mach/clock.h>
#include <mach/mach.h>
#endif

COptionsDateTimeTab::COptionsDateTimeTab(QWidget *parent)
    : IOptionsTab(parent)
    , ui(new Ui::COptionsDateTimeTab)
{
    ui->setupUi(this);

    ui->btDayMinus->setType(CToolButton::ScrollDown);
    ui->btDayPlus->setType(CToolButton::ScrollUp);
    ui->btMonthMinus->setType(CToolButton::ScrollDown);
    ui->btMonthPlus->setType(CToolButton::ScrollUp);
    ui->btYearMinus->setType(CToolButton::ScrollDown);
    ui->btYearPlus->setType(CToolButton::ScrollUp);
    ui->btHourMinus->setType(CToolButton::ScrollDown);
    ui->btHourPlus->setType(CToolButton::ScrollUp);
    ui->btMinuteMinus->setType(CToolButton::ScrollDown);
    ui->btMinutePlus->setType(CToolButton::ScrollUp);

    QDate today(QDate::currentDate());
    ui->btDay->setText(QString::number(today.day()));
    ui->btMonth->setText(QString::number(today.month()));
    ui->btYear->setText(QString::number(today.year()));
    QTime now(QTime::currentTime());
    ui->btHour->setText(QString::number(now.hour()));
    ui->btMinute->setText(QString::number(now.minute()));

    connect(ui->btDay, &QPushButton::clicked, this, &COptionsDateTimeTab::btDayClicked);
    connect(ui->btMonth, &QPushButton::clicked, this, &COptionsDateTimeTab::btMonthClicked);
    connect(ui->btYear, &QPushButton::clicked, this, &COptionsDateTimeTab::btYearClicked);
    connect(ui->btHour, &QPushButton::clicked, this, &COptionsDateTimeTab::btHourClicked);
    connect(ui->btMinute, &QPushButton::clicked, this, &COptionsDateTimeTab::btMinuteClicked);


    connect(ui->btDayPlus, &QPushButton::clicked, this, &COptionsDateTimeTab::btDayPPressed);
    connect(ui->btDayMinus, &QPushButton::clicked, this, &COptionsDateTimeTab::btDayMPressed);
    connect(ui->btMonthPlus, &QPushButton::clicked, this, &COptionsDateTimeTab::btMonthPPressed);
    connect(ui->btMonthMinus, &QPushButton::clicked, this, &COptionsDateTimeTab::btMonthMPressed);
    connect(ui->btYearPlus, &QPushButton::clicked, this, &COptionsDateTimeTab::btYearPPressed);
    connect(ui->btYearMinus, &QPushButton::clicked, this, &COptionsDateTimeTab::btYearMPressed);
    connect(ui->btHourPlus, &QPushButton::clicked, this, &COptionsDateTimeTab::btHourPPressed);
    connect(ui->btHourMinus, &QPushButton::clicked, this, &COptionsDateTimeTab::btHourMPressed);
    connect(ui->btMinutePlus, &QPushButton::clicked, this, &COptionsDateTimeTab::btMinutePPressed);
    connect(ui->btMinuteMinus, &QPushButton::clicked, this, &COptionsDateTimeTab::btMinuteMPressed);

    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
//    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
//            this, &IOptionsTab::backTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &COptionsDateTimeTab::slotBackPressed);

}

COptionsDateTimeTab::~COptionsDateTimeTab()
{
    delete ui;
}
void COptionsDateTimeTab::slotBackPressed(){
      apply();
      emit backTriggered();
}

void COptionsDateTimeTab::btYearPPressed()
{
    int var = getYear() + 1;
    ui->btYear->setText(QString::number(var));
}

void COptionsDateTimeTab::btMonthPPressed()
{
    int var = getMonth();
    if (var == 12) var=1;
    else ++var;

    ui->btMonth->setText(QString::number(var));
}

void COptionsDateTimeTab::btDayPPressed()
{
    int var = getDay()+1;
    QDate date(getYear(), getMonth(), var);
    if (!date.isValid())
        var = 1;

    ui->btDay->setText(QString::number(var));
}

void COptionsDateTimeTab::btHourPPressed()
{
    int var = getHour();
    if (var == 24) var=1;
    else ++var;

    ui->btHour->setText(QString::number(var));
}

void COptionsDateTimeTab::btMinutePPressed()
{
    int var = getMinute();
    if (var == 60) var=1;
    else ++var;

    ui->btMinute->setText(QString::number(var));
}

void COptionsDateTimeTab::btYearMPressed()
{
    int var = getYear() - 1;
    ui->btYear->setText(QString::number(var));
}

void COptionsDateTimeTab::btMonthMPressed()
{
    int var = getMonth();
    if (var == 1)
        var=12;
    else
        --var;

    ui->btMonth->setText(QString::number(var));
}

void COptionsDateTimeTab::btDayMPressed()
{
    int var = getDay()-1;
    QDate date(getYear(), getMonth(), var);
    if (!date.isValid())
    {
        date.setDate(getYear(), getMonth(), 1);
        var = date.daysInMonth();
    }

    ui->btDay->setText(QString::number(var));
}

void COptionsDateTimeTab::btHourMPressed()
{
    int var = getHour();
    if(var == 1) var=24;
    else --var;

    ui->btHour->setText(QString::number(var));
}

void COptionsDateTimeTab::btMinuteMPressed()
{
    int var = getMinute();
    if(var == 1) var=60;
    else --var;

    ui->btMinute->setText(QString::number(var));
}

void COptionsDateTimeTab::btDayClicked()
{
    int value = getDay();
    if (CNumericalKeyboardDialog::getInteger(value, tr("Select day"))) {
        value = qMax(qMin(value, 31), 1);
        QDate date(getYear(), getMonth(), value);
        if (!date.isValid())
            value = 1;
        ui->btDay->setText(QString::number(value));
    }
}

void COptionsDateTimeTab::btMonthClicked()
{
    int value = getMonth();
    if (CNumericalKeyboardDialog::getInteger(value, tr("Select month"))) {
        value = qMax(qMin(value, 12), 1);
        ui->btMonth->setText(QString::number(value));
    }
}

void COptionsDateTimeTab::btYearClicked()
{
    int value = getYear();
    if (CNumericalKeyboardDialog::getInteger(value, tr("Select year"))) {
        ui->btYear->setText(QString::number(value));
    }
}

void COptionsDateTimeTab::btHourClicked()
{
    int value = getHour();
    if (CNumericalKeyboardDialog::getInteger(value, tr("Select hour"))) {
        value = qMax(qMin(value, 24), 1);
        ui->btHour->setText(QString::number(value));
    }
}

void COptionsDateTimeTab::btMinuteClicked()
{
    int value = getMinute();
    if (CNumericalKeyboardDialog::getInteger(value, tr("Select minute"))) {
        value = qMax(qMin(value, 60), 1);
        ui->btMinute->setText(QString::number(value));
    }
}

void COptionsDateTimeTab::apply()
{
    const QDateTime newValue = getDateTime();
    const QTime now = QTime::currentTime();
    QDateTime oldValue(QDate::currentDate(), QTime(now.hour(), now.minute()));
    if (newValue != oldValue) {
        qCDebug(COTGUI_LOG) << "Setting new date/time" << newValue;
#ifdef Q_OS_UNIX
        struct timespec ts;
        ts.tv_sec = newValue.toMSecsSinceEpoch() / 1000;
        ts.tv_nsec = 0;

#if defined(Q_OS_MAC)
        clock_serv_t cclock;
        host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);

        struct mach_timespec mts;
        mts.tv_sec = ts.tv_sec;
        mts.tv_nsec = ts.tv_nsec;

        if (clock_set_time(cclock, mts) != KERN_SUCCESS) {
            qWarning() << "Couldn't set system time:" << strerror(errno);
        }

        mach_port_deallocate(mach_task_self(), cclock);
#else
        if (clock_settime(CLOCK_REALTIME, &ts) != 0) {
            qWarning() << "Couldn't set system time:" << strerror(errno);
        }
#ifdef DEVICE_BUILD
        QProcess process;
        const QString command = "hwclock";
        const QStringList parameters = QStringList()
                << "-w";

        process.setProcessChannelMode(QProcess::MergedChannels);
        process.start(command, parameters);
        process.waitForFinished(-1);
        if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {

            qDebug("%s: Set RTC fail: \n", Q_FUNC_INFO);
    }
#endif

#endif

#else
        qWarning() << "This OS is not supported!";
#endif
    }
}

int COptionsDateTimeTab::getYear() const
{
    return ui->btYear->text().toInt();
}

int COptionsDateTimeTab::getMonth() const
{
    return ui->btMonth->text().toInt();
}

int COptionsDateTimeTab::getDay() const
{
    return ui->btDay->text().toInt();
}

int COptionsDateTimeTab::getHour() const
{
    return ui->btHour->text().toInt();
}

int COptionsDateTimeTab::getMinute() const
{
    return ui->btMinute->text().toInt();
}

QDateTime COptionsDateTimeTab::getDateTime() const
{
    return QDateTime(QDate(getYear(), getMonth(), getDay()), QTime(getHour(), getMinute()));
}
