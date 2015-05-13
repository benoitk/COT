#ifndef CEDITINBINDSTAB_H
#define CEDITINBINDSTAB_H

#include "IConfiguratorEditTab.h"

class IVariable;
class CEditInBindsUIHandler;

class CEditInBindsTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditInBindsTab(QWidget *parent = Q_NULLPTR);

    void setVariables(IVariable *ivar);
    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditInBindsUIHandler *m_configuratorUIHandler;
};

#endif // CEDITINBINDSTAB_H
