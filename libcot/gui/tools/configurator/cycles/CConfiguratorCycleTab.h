#ifndef CCONFIGURATORCYCLETAB_H
#define CCONFIGURATORCYCLETAB_H

#include "IConfiguratorTab.h"

class CConfiguratorCycleTabUIHandler;

class CConfiguratorCycleTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorCycleTab(QWidget *parent = Q_NULLPTR);

protected slots:
    void slotAddCycle();
    void slotUpdateLayout();

private:
    CConfiguratorCycleTabUIHandler *m_handler;
};

#endif // CCONFIGURATORCYCLETAB_H
