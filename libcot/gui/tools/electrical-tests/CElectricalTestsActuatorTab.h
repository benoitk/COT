#ifndef CELECTRICALTESTSACTUATORTAB_H
#define CELECTRICALTESTSACTUATORTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsActuatorTab;
}

class CElectricalTestsActuatorTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsActuatorTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsActuatorTab();

private:
    Ui::CElectricalTestsActuatorTab *ui;
};

#endif // CELECTRICALTESTSACTUATORTAB_H
