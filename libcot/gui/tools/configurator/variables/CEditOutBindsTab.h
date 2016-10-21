#ifndef CEDITOUTBINDSTAB_H
#define CEDITOUTBINDSTAB_H

#include "IConfiguratorEditTab.h"

class CEditOutBindsUIHandler;
class IVariable;
class CAutomate;
class CEditOutBindsTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditOutBindsTab(CAutomate* arg_automate, IVariable *ivar, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditOutBindsUIHandler *m_handler;
    CAutomate* m_automate;

private slots:
    void slotAddBinding();
};

#endif // CEDITOUTBINDSTAB_H
