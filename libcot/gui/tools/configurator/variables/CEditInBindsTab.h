#ifndef CEDITINBINDSTAB_H
#define CEDITINBINDSTAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditInBindsTab;
}
class IConfiguratorUIHandler;
class IVariable;
class CEditInBindsTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditInBindsTab(QWidget *parent = Q_NULLPTR);
    ~CEditInBindsTab();

    void setVariables(const QString &variableName);
private:
    Ui::CEditInBindsTab *ui;
    IConfiguratorUIHandler *m_configuratorUIHandler;
};

#endif // CEDITINBINDSTAB_H
