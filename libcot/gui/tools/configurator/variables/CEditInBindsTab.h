#ifndef CEDITINBINDSTAB_H
#define CEDITINBINDSTAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditInBindsTab;
}
class ConfiguratorUIHandler;
class IVariable;
class CEditInBindsTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditInBindsTab(QWidget *parent = Q_NULLPTR);
    ~CEditInBindsTab();

    void setVariables(const QList<IVariable *> &variables);
private:
    Ui::CEditInBindsTab *ui;
    ConfiguratorUIHandler *m_configuratorUIHandler;
};

#endif // CEDITINBINDSTAB_H
