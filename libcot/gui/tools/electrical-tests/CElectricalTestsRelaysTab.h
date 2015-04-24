#ifndef CELECTRICALTESTSRELAYSTAB_H
#define CELECTRICALTESTSRELAYSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsRelaysTab;
}

class IVariableUIHandler;

class CElectricalTestsRelaysTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsRelaysTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsRelaysTab();

protected Q_SLOTS:
    void updateElecTestRelays();

private:
    Ui::CElectricalTestsRelaysTab *ui;
    IVariableUIHandler *m_elecTestRelaysHandler;
};

#endif // CELECTRICALTESTSRELAYSTAB_H
