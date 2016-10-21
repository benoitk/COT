#ifndef CELECTRICALTESTSPUMPSTAB_H
#define CELECTRICALTESTSPUMPSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsPumpsTab;
}

class IVariableUIHandler;
class CAutomate;
class CElectricalTestsPumpsTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsPumpsTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsPumpsTab();

protected slots:
    void updateElecTestPump();

private:
    Ui::CElectricalTestsPumpsTab *ui;
    IVariableUIHandler *m_elecTestPumpHandler;
    CAutomate* m_automate;
};

#endif // CELECTRICALTESTSPUMPSTAB_H
