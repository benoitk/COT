#ifndef CMEASURESTREAMTAB_H
#define CMEASURESTREAMTAB_H

#include "IMeasureTab.h"

namespace Ui {
class CMeasureStreamTab;
}

class CMeasureStreamTab : public IMeasureTab
{
    Q_OBJECT

public:
    explicit CMeasureStreamTab(QWidget *parent = Q_NULLPTR);
    ~CMeasureStreamTab();

private:
    Ui::CMeasureStreamTab *ui;
};

#endif // CMEASURESTREAMTAB_H
