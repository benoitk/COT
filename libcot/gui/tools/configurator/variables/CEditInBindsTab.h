#ifndef CEDITINBINDSTAB_H
#define CEDITINBINDSTAB_H

#include "IConfiguratorEditTab.h"

class IVariable;
class CEditInBindsUIHandler;
class CAutomate;
class CEditInBindsTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditInBindsTab(CAutomate* arg_automate, IVariable *ivar, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditInBindsUIHandler *m_handler;
};

#endif // CEDITINBINDSTAB_H
