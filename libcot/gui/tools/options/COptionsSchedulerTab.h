#ifndef COPTIONSSCHEDULERTAB_H
#define COPTIONSSCHEDULERTAB_H

#include "IOptionsTab.h"

namespace Ui {
class COptionsSchedulerTab;
}

class COptionsSchedulerTab : public IOptionsTab
{
    Q_OBJECT

public:
    explicit COptionsSchedulerTab(QWidget *parent = Q_NULLPTR);
    ~COptionsSchedulerTab();

private:
    Ui::COptionsSchedulerTab *ui;
};

#endif // COPTIONSSCHEDULERTAB_H
