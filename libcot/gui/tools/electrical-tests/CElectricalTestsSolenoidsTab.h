#ifndef CELECTRICALTESTSSOLENOIDSTAB_H
#define CELECTRICALTESTSSOLENOIDSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsSolenoidsTab;
}

class IVariableUIHandler;

class CElectricalTestsSolenoidsTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsSolenoidsTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsSolenoidsTab();

protected slots:
    void updateElecTestRelays();

private:
    Ui::CElectricalTestsSolenoidsTab *ui;
    IVariableUIHandler *m_elecTestRelaysHandler;
};

#endif // CELECTRICALTESTSSOLENOIDSTAB_H
