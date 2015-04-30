#ifndef CCONFIGURATORCYCLETAB_H
#define CCONFIGURATORCYCLETAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorCycleTab;
}
class CConfiguratorCycleTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorCycleTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorCycleTab();
private:
    Ui::CConfiguratorCycleTab *ui;
};

#endif // CCONFIGURATORCYCLETAB_H
