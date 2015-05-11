#ifndef CCONFIGURATORCYCLETAB_H
#define CCONFIGURATORCYCLETAB_H

#include "IConfiguratorTab.h"

namespace Ui {
class CConfiguratorCycleTab;
}

class CConfiguratorCycleTabUIHandler;

class CConfiguratorCycleTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorCycleTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorCycleTab();

protected slots:
    void slotAddCycle();
    void slotUpdateLayout();

private:
    Ui::CConfiguratorCycleTab *ui;
    CConfiguratorCycleTabUIHandler *m_handler;
};

#endif // CCONFIGURATORCYCLETAB_H
