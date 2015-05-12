#ifndef CEDITOUTBINDSTAB_H
#define CEDITOUTBINDSTAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditOutBindsTab;
}
class IConfiguratorUIHandler;
class IVariable;
class CEditOutBindsTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditOutBindsTab(QWidget *parent = Q_NULLPTR);
    ~CEditOutBindsTab();
    void setVariables(IVariable *ivar);
    void applyProperties(IVariable *ivar) Q_DECL_OVERRIDE;
private:
    Ui::CEditOutBindsTab *ui;
    IConfiguratorUIHandler *m_configuratorUIHandler;
};

#endif // CEDITOUTBINDSTAB_H
