#ifndef CELECTRICALTESTSSOLENOIDSTAB_H
#define CELECTRICALTESTSSOLENOIDSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsSolenoidsTab;
}

class IVariableUIHandler;
class CAutomate;
class CElectricalTestsSolenoidsTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsSolenoidsTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsSolenoidsTab();

protected slots:
    void updateElecTestRelays();

private:
    Ui::CElectricalTestsSolenoidsTab *ui;
    IVariableUIHandler *m_elecTestRelaysHandler;
    CAutomate* m_automate;
};

#endif // CELECTRICALTESTSSOLENOIDSTAB_H
