#ifndef CELECTRICALTESTSPUMPSTAB_H
#define CELECTRICALTESTSPUMPSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsPumpsTab;
}

class CElectricalTestsPumpsTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsPumpsTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsPumpsTab();

private:
    Ui::CElectricalTestsPumpsTab *ui;
};

#endif // CELECTRICALTESTSPUMPSTAB_H
