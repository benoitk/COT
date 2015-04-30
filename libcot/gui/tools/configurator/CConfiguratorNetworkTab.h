#ifndef CCONFIGURATORNETWORKTAB_H
#define CCONFIGURATORNETWORKTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorNetworkTab;
}
class CConfiguratorNetworkTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorNetworkTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorNetworkTab();
private:
    Ui::CConfiguratorNetworkTab *ui;
};

#endif // CCONFIGURATORNETWORKTAB_H
