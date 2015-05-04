#ifndef CCONFIGURATORSTREAMSTAB_H
#define CCONFIGURATORSTREAMSTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorStreamsTab;
}
class IVariableUIHandler;
class CConfiguratorStreamsTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorStreamsTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorStreamsTab();
private slots:
    void addVariable();
private:
    IVariableUIHandler *m_ivariableUIHandler;
    Ui::CConfiguratorStreamsTab *ui;
};

#endif // CCONFIGURATORSTREAMSTAB_H
