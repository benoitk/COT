#ifndef CELECTRICALTESTSACTUATORTAB_H
#define CELECTRICALTESTSACTUATORTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsActuatorTab;
}

class IVariableUIHandler;


class CElectricalTestsActuatorTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsActuatorTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsActuatorTab();

protected slots:
    void updateElecTestActuator();


private:
    Ui::CElectricalTestsActuatorTab *ui;
    IVariableUIHandler *m_elecTestActuatorHandler;
};

#endif // CELECTRICALTESTSACTUATORTAB_H
