#ifndef CCONFIGURATORCYCLETAB_H
#define CCONFIGURATORCYCLETAB_H

#include "IConfiguratorTab.h"

class CConfiguratorCycleTabUIHandler;
class CAutomate;
class CConfiguratorCycleTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorCycleTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);

protected slots:
    void slotAddCycle();
    void slotUpdateLayout();

private:
    CConfiguratorCycleTabUIHandler *m_handler;
    CAutomate* m_automate;
};

#endif // CCONFIGURATORCYCLETAB_H
