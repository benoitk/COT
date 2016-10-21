#ifndef CELECTRICALTESTSRELAYSTAB_H
#define CELECTRICALTESTSRELAYSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsRelaysTab;
}

class IVariableUIHandler;
class CAutomate;
class CElectricalTestsRelaysTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsRelaysTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsRelaysTab();

protected slots:
    void updateElecTestRelays();

private:
    Ui::CElectricalTestsRelaysTab *ui;
    IVariableUIHandler *m_elecTestRelaysHandler;
    CAutomate* m_automate;
};

#endif // CELECTRICALTESTSRELAYSTAB_H
