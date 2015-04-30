#ifndef CCONFIGURATORHARDWARETAB_H
#define CCONFIGURATORHARDWARETAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorHardwareTab;
}
class CConfiguratorHardwareTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorHardwareTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorHardwareTab();
private:
    Ui::CConfiguratorHardwareTab *ui;
};

#endif // CCONFIGURATORHARDWARETAB_H
