#ifndef COPTIONSDATETIMETAB_H
#define COPTIONSDATETIMETAB_H

#include "IOptionsTab.h"

namespace Ui {
class COptionsDateTimeTab;
}

class COptionsDateTimeTab : public IOptionsTab
{
    Q_OBJECT

public:
    explicit COptionsDateTimeTab(QWidget *parent = Q_NULLPTR);
    ~COptionsDateTimeTab();

private Q_SLOTS:
    void btDayPPressed();
    void btDayMPressed();
    void btMonthPPressed();
    void btMonthMPressed();
    void btYearPPressed();
    void btYearMPressed();
    void btHourPPressed();
    void btHourMPressed();
    void btMinutePPressed();
    void btMinuteMPressed();

    void btDayClicked();
    void btMonthClicked();
    void btYearClicked();
    void btHourClicked();
    void btMinuteClicked();

private:
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;

    Ui::COptionsDateTimeTab *ui;
};

#endif // COPTIONSDATETIMETAB_H
