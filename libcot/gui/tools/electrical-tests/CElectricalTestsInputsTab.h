#ifndef CELECTRICALTESTSINPUTSTAB_H
#define CELECTRICALTESTSINPUTSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsInputsTab;
}

class CElectricalTestsInputsTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsInputsTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsInputsTab();

private:
    Ui::CElectricalTestsInputsTab *ui;
};

#endif // CELECTRICALTESTSINPUTSTAB_H
