#ifndef COPTIONSOPTIONSTAB_H
#define COPTIONSOPTIONSTAB_H

#include "IOptionsTab.h"

namespace Ui {
class COptionsOptionsTab;
}

class COptionsOptionsTab : public IOptionsTab
{
    Q_OBJECT

public:
    explicit COptionsOptionsTab(QWidget *parent = Q_NULLPTR);
    ~COptionsOptionsTab();

private:
    Ui::COptionsOptionsTab *ui;
};

#endif // COPTIONSOPTIONSTAB_H
