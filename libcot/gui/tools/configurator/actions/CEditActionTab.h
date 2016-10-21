#ifndef CEDITACTIONTAB_H
#define CEDITACTIONTAB_H

#include "IConfiguratorEditTab.h"

class CEditActionTabUIHandler;
class IAction;
class CAutomate;
class CEditActionTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditActionTab(CAutomate* arg_automate, IAction *action, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditActionTabUIHandler *m_handler;
};

#endif // CEDITACTIONTAB_H
