#ifndef CELECTRICALTESTSACTUATORTAB_H
#define CELECTRICALTESTSACTUATORTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsActuatorTab;
}

class IVariableUIHandler;

class CAutomate;
class CElectricalTestsActuatorTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsActuatorTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsActuatorTab();

protected slots:
    void updateElecTestActuator();


private:
    Ui::CElectricalTestsActuatorTab *ui;
    IVariableUIHandler *m_elecTestActuatorHandler;
    CAutomate* m_automate;
};

#endif // CELECTRICALTESTSACTUATORTAB_H
