#ifndef CEDITCYCLETAB_H
#define CEDITCYCLETAB_H

#include "IConfiguratorEditTab.h"

class ICycle;
class CEditCycleTabUIHandler;
class CAutomate;
class CEditCycleTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditCycleTab(CAutomate* arg_automate, ICycle *cycle, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditCycleTabUIHandler *m_handler;
    CAutomate* m_automate;
};

#endif // CEDITCYCLETAB_H
