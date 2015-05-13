#ifndef CCONFIGURATORSTREAMSTAB_H
#define CCONFIGURATORSTREAMSTAB_H

#include "IConfiguratorTab.h"

class ConfiguratorStreamsUIHandler;

class CConfiguratorStreamsTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorStreamsTab(QWidget *parent = Q_NULLPTR);

private slots:
    void slotAddStreams();

private:
    ConfiguratorStreamsUIHandler *m_istreamUIHandler;
};

#endif // CCONFIGURATORSTREAMSTAB_H
