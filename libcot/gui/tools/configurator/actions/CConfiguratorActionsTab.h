#ifndef CCONFIGURATORACTIONSTAB_H
#define CCONFIGURATORACTIONSTAB_H

#include "IConfiguratorTab.h"

class ConfiguratorActionsUIHandler;

/**
 * Tab "Actions" in the configurator GUI.
 */
class CConfiguratorActionsTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorActionsTab(QWidget *parent = Q_NULLPTR);

private slots:
    void slotAddAction();
    void slotUpdateLayout();

private:
    ConfiguratorActionsUIHandler *m_iactionUIHandler;
};

#endif // CCONFIGURATORACTIONSTAB_H
