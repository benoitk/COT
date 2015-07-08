#ifndef CEDITOUTBINDSTAB_H
#define CEDITOUTBINDSTAB_H

#include "IConfiguratorEditTab.h"

class CEditOutBindsUIHandler;
class IVariable;

class CEditOutBindsTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditOutBindsTab(IVariable *ivar, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditOutBindsUIHandler *m_handler;

private slots:
    void slotAddBinding();
};

#endif // CEDITOUTBINDSTAB_H
