#ifndef CCONFIGURATORDISPLAYTAB_H
#define CCONFIGURATORDISPLAYTAB_H

#include "IConfiguratorTab.h"

class CConfiguratorDisplayTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorDisplayTab(QWidget *parent = Q_NULLPTR);
};

#endif // CCONFIGURATORDISPLAYTAB_H
