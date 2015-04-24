#ifndef CELECTRICALTESTS420TAB_H
#define CELECTRICALTESTS420TAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTests420Tab;
}

class IVariableUIHandler;

class CElectricalTests420Tab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTests420Tab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTests420Tab();

protected slots:
    void updateElecTest420();

private:
    Ui::CElectricalTests420Tab *ui;
    IVariableUIHandler *m_elecTest420Handler;
};

#endif // CELECTRICALTESTS420TAB_H
