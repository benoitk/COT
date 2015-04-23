#ifndef CMEASURESTREAMTAB_H
#define CMEASURESTREAMTAB_H

#include "IMeasureTab.h"

namespace Ui {
class CMeasureStreamTab;
}

class IVariableUIHandler;

class CMeasureStreamTab : public IMeasureTab
{
    Q_OBJECT

public:
    explicit CMeasureStreamTab(const QStringList &variables, QWidget *parent = Q_NULLPTR);
    ~CMeasureStreamTab();

private:
    Ui::CMeasureStreamTab *ui;
    IVariableUIHandler *m_variableHandler;
};

#endif // CMEASURESTREAMTAB_H
