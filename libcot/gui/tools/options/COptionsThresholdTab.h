#ifndef COPTIONSTHRESHOLDTAB_H
#define COPTIONSTHRESHOLDTAB_H

#include "IOptionsTab.h"

namespace Ui {
class COptionsThresholdTab;
}

class COptionsThresholdTab : public IOptionsTab
{
    Q_OBJECT

public:
    explicit COptionsThresholdTab(QWidget *parent = Q_NULLPTR);
    ~COptionsThresholdTab();

private:
    Ui::COptionsThresholdTab *ui;
};

#endif // COPTIONSTHRESHOLDTAB_H
