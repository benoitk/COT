#include "COptionsDateTimeTab.h"
#include "ui_COptionsDateTimeTab.h"

#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <CNumericalKeyboardDialog.h>

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
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IOptionsTab::backTriggered);
}

COptionsDateTimeTab::~COptionsDateTimeTab()
{
    delete ui;
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
