#ifndef COPTIONSAUTOCYCLESTAB_H
#define COPTIONSAUTOCYCLESTAB_H

#include "IOptionsTab.h"

namespace Ui {
class COptionsAutoCyclesTab;
}

class COptionsAutoCyclesTab : public IOptionsTab
{
    Q_OBJECT

public:
    explicit COptionsAutoCyclesTab(QWidget *parent = Q_NULLPTR);
    ~COptionsAutoCyclesTab();

private:
    Ui::COptionsAutoCyclesTab *ui;
};

#endif // COPTIONSAUTOCYCLESTAB_H
