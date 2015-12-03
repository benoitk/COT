#ifndef CELECTRICALTESTS420TAB_H
#define CELECTRICALTESTS420TAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTests420Tab;
}

class IVariableUIHandler;
class CVariableBool;
class IVariable;
class CElectricalTests420Tab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTests420Tab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTests420Tab();

protected slots:
    void updateElecTest420();

private slots:
    void slotOneOfBtTestsClicked(IVariable*);

private:
    Ui::CElectricalTests420Tab *ui;
    IVariableUIHandler *m_elecTest420Handler;
    QList<CVariableBool*> m_listBtTests;
    QMap<QString, IVariable*> m_mapVar;
};

#endif // CELECTRICALTESTS420TAB_H
