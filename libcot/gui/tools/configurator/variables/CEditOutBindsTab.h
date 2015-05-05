#ifndef CEDITOUTBINDSTAB_H
#define CEDITOUTBINDSTAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditOutBindsTab;
}
class ConfiguratorUIHandler;
class IVariable;
class CEditOutBindsTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditOutBindsTab(QWidget *parent = Q_NULLPTR);
    ~CEditOutBindsTab();
    void setVariables(const QList<IVariable *> &variables);
private:
    Ui::CEditOutBindsTab *ui;
    ConfiguratorUIHandler *m_configuratorUIHandler;
};

#endif // CEDITOUTBINDSTAB_H
