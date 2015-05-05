#ifndef CEDITINBINDSTAB_H
#define CEDITINBINDSTAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditInBindsTab;
}
class ConfiguratorUIHandler;
class CEditInBindsTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditInBindsTab(QWidget *parent = Q_NULLPTR);
    ~CEditInBindsTab();
private:
    Ui::CEditInBindsTab *ui;
    ConfiguratorUIHandler *m_configuratorUIHandler;
};

#endif // CEDITINBINDSTAB_H
