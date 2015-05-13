#ifndef CCONFIGURATORNETWORKTAB_H
#define CCONFIGURATORNETWORKTAB_H

#include "IConfiguratorTab.h"

class CConfiguratorNetworkTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorNetworkTab(QWidget *parent = Q_NULLPTR);
};

#endif // CCONFIGURATORNETWORKTAB_H
