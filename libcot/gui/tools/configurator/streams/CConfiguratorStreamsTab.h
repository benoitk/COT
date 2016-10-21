#ifndef CCONFIGURATORSTREAMSTAB_H
#define CCONFIGURATORSTREAMSTAB_H

#include "IConfiguratorTab.h"

class ConfiguratorStreamsUIHandler;
class CAutomate;
class CConfiguratorStreamsTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorStreamsTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);

private:
    ConfiguratorStreamsUIHandler *m_istreamUIHandler;
};

#endif // CCONFIGURATORSTREAMSTAB_H
