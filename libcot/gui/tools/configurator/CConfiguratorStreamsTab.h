#ifndef CCONFIGURATORSTREAMSTAB_H
#define CCONFIGURATORSTREAMSTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorStreamsTab;
}
class ConfiguratorStreamsUIHandler;
class CConfiguratorStreamsTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorStreamsTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorStreamsTab();
private slots:
    void slotAddStreams();
private:
    ConfiguratorStreamsUIHandler *m_istreamUIHandler;
    Ui::CConfiguratorStreamsTab *ui;
};

#endif // CCONFIGURATORSTREAMSTAB_H
