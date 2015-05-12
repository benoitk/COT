#ifndef CEDITINBINDSTAB_H
#define CEDITINBINDSTAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditInBindsTab;
}
class IVariable;
class CEditInBindsUIHandler;
class CEditInBindsTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditInBindsTab(QWidget *parent = Q_NULLPTR);
    ~CEditInBindsTab();

    void setVariables(IVariable *ivar);
    void applyProperties(IVariable *ivar) Q_DECL_OVERRIDE;
private:
    Ui::CEditInBindsTab *ui;
    CEditInBindsUIHandler *m_configuratorUIHandler;
};

#endif // CEDITINBINDSTAB_H
