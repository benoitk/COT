#ifndef CEDITOUTBINDSTAB_H
#define CEDITOUTBINDSTAB_H

#include "IConfiguratorEditTab.h"

class CEditOutBindsUIHandler;
class IVariable;

class CEditOutBindsTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditOutBindsTab(QWidget *parent = Q_NULLPTR);

    void setVariables(IVariable *ivar);
    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditOutBindsUIHandler *m_configuratorUIHandler;
};

#endif // CEDITOUTBINDSTAB_H
