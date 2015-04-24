#ifndef CELECTRICALTESTSPUMPSTAB_H
#define CELECTRICALTESTSPUMPSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsPumpsTab;
}

class IVariableUIHandler;

class CElectricalTestsPumpsTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsPumpsTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsPumpsTab();

protected Q_SLOTS:
    void updateElecTestPump();

private:
    Ui::CElectricalTestsPumpsTab *ui;
    IVariableUIHandler *m_elecTestPumpHandler;
};

#endif // CELECTRICALTESTSPUMPSTAB_H
