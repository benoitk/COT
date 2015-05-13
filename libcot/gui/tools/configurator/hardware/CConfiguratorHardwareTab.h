#ifndef CCONFIGURATORHARDWARETAB_H
#define CCONFIGURATORHARDWARETAB_H

#include "IConfiguratorTab.h"

class CConfiguratorHardwareTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorHardwareTab(QWidget *parent = Q_NULLPTR);
};

#endif // CCONFIGURATORHARDWARETAB_H
