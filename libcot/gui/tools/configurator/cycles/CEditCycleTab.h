#ifndef CEDITCYCLETAB_H
#define CEDITCYCLETAB_H

#include "IConfiguratorEditTab.h"

class ICycle;
class CEditCycleTabUIHandler;

class CEditCycleTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditCycleTab(ICycle *cycle, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditCycleTabUIHandler *m_handler;
};

#endif // CEDITCYCLETAB_H
