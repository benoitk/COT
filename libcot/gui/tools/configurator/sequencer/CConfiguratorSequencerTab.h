#ifndef CCONFIGURATORSEQUENCERTAB_H
#define CCONFIGURATORSEQUENCERTAB_H

#include "IConfiguratorTab.h"

class ConfiguratorSequencerUIHandler;

class CConfiguratorSequencerTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorSequencerTab(QWidget *parent = Q_NULLPTR);

private slots:
    void slotUpdateLayout();
    void slotAddSequencer();

private:
    ConfiguratorSequencerUIHandler *m_isequencerUIHandler;
};

#endif // CCONFIGURATORSEQUENCERTAB_H
