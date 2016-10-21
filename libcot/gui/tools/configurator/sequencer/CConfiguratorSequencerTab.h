#ifndef CCONFIGURATORSEQUENCERTAB_H
#define CCONFIGURATORSEQUENCERTAB_H

#include "IConfiguratorTab.h"

class ConfiguratorSequencerUIHandler;
class CAutomate;
class CConfiguratorSequencerTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorSequencerTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);

private slots:
    void slotUpdateLayout();
    void slotAddSequencer();

private:
    ConfiguratorSequencerUIHandler *m_handler;
    CAutomate* m_automate;
};

#endif // CCONFIGURATORSEQUENCERTAB_H
