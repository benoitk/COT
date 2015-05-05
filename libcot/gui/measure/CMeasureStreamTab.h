#ifndef CMEASURESTREAMTAB_H
#define CMEASURESTREAMTAB_H

#include "IMeasureTab.h"

namespace Ui {
class CMeasureStreamTab;
}

class IVariable;
class IVariableUIHandler;

typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;

class CMeasureStreamTab : public IMeasureTab
{
    Q_OBJECT

public:
    explicit CMeasureStreamTab(const IVariablePtrList &variables, QWidget *parent = Q_NULLPTR);
    ~CMeasureStreamTab();

private:
    Ui::CMeasureStreamTab *ui;
    IVariableUIHandler *m_variableHandler;
};

#endif // CMEASURESTREAMTAB_H
