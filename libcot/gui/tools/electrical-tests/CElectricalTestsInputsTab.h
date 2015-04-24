#ifndef CELECTRICALTESTSINPUTSTAB_H
#define CELECTRICALTESTSINPUTSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsInputsTab;
}

class IVariableUIHandler;

class CElectricalTestsInputsTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsInputsTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsInputsTab();

protected Q_SLOTS:
    void updateElecTestInputs();

private:
    Ui::CElectricalTestsInputsTab *ui;
    IVariableUIHandler *m_elecTestInputsHandler;
};

#endif // CELECTRICALTESTSINPUTSTAB_H
