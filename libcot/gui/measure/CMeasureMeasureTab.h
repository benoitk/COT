#ifndef CMEASUREMEASURETAB_H
#define CMEASUREMEASURETAB_H

#include "IMeasureTab.h"

namespace Ui {
class CMeasureMeasureTab;
}

class IVariable;
class IVariableUIHandler;

typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;
class CAutomate;
class CMeasureMeasureTab : public IMeasureTab
{
    Q_OBJECT

public:
    explicit CMeasureMeasureTab(CAutomate* arg_automate, const IVariablePtrList &variables, QWidget *parent = Q_NULLPTR);
    ~CMeasureMeasureTab();

private:
    Ui::CMeasureMeasureTab *ui;
    IVariableUIHandler *m_variableHandler;
};

#endif // CMEASUREMEASURETAB_H
