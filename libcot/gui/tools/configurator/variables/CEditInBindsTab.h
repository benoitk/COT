#ifndef CEDITINBINDSTAB_H
#define CEDITINBINDSTAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditInBindsTab;
}
class CEditInBindsTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditInBindsTab(QWidget *parent = Q_NULLPTR);
    ~CEditInBindsTab();
private:
    Ui::CEditInBindsTab *ui;
};

#endif // CEDITINBINDSTAB_H
