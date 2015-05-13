#ifndef CCONFIGURATORSEQUENCERTAB_H
#define CCONFIGURATORSEQUENCERTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorSequencerTab;
}
class ConfiguratorSequencerUIHandler;
class CConfiguratorSequencerTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorSequencerTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorSequencerTab();
private slots:
    void slotAddSequencer();
private:
    Ui::CConfiguratorSequencerTab *ui;
    ConfiguratorSequencerUIHandler *m_isequencerUIHandler;
};

#endif // CCONFIGURATORSEQUENCERTAB_H
