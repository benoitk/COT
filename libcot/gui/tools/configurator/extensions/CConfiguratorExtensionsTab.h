#ifndef CCONFIGURATOREXTENSIONSTAB_H
#define CCONFIGURATOREXTENSIONSTAB_H

#include "IConfiguratorTab.h"

class CConfiguratorExtensionsTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorExtensionsTab(QWidget *parent = Q_NULLPTR);
};

#endif // CCONFIGURATOREXTENSIONSTAB_H
