#ifndef CCONFIGURATORSEQUENCERTAB_H
#define CCONFIGURATORSEQUENCERTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorSequencerTab;
}
class CConfiguratorSequencerTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorSequencerTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorSequencerTab();
private:
    Ui::CConfiguratorSequencerTab *ui;
};

#endif // CCONFIGURATORSEQUENCERTAB_H
