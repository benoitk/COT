#ifndef CMEASUREMEASURETAB_H
#define CMEASUREMEASURETAB_H

#include "IMeasureTab.h"

namespace Ui {
class CMeasureMeasureTab;
}

class CMeasureMeasureTab : public IMeasureTab
{
    Q_OBJECT

public:
    explicit CMeasureMeasureTab(QWidget *parent = Q_NULLPTR);
    ~CMeasureMeasureTab();

private:
    Ui::CMeasureMeasureTab *ui;
};

#endif // CMEASUREMEASURETAB_H
