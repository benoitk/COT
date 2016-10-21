#ifndef CELECTRICALTESTSINPUTSTAB_H
#define CELECTRICALTESTSINPUTSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsInputsTab;
}

class IVariableUIHandler;
class IVariable;
class CAutomate;
class CElectricalTestsInputsTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsInputsTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsInputsTab();

protected slots:
    void updateElecTestInputs();
 public slots:
    void slotUpdateInput();

private:
    Ui::CElectricalTestsInputsTab *ui;
    IVariableUIHandler *m_elecTestInputsHandler;
    QList<IVariable*> m_listInputVar;
    CAutomate* m_automate;
};

#endif // CELECTRICALTESTSINPUTSTAB_H
