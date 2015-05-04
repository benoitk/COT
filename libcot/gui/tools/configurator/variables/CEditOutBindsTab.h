#ifndef CEDITOUTBINDSTAB_H
#define CEDITOUTBINDSTAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditOutBindsTab;
}
class CEditOutBindsTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditOutBindsTab(QWidget *parent = Q_NULLPTR);
    ~CEditOutBindsTab();
private:
    Ui::CEditOutBindsTab *ui;
};

#endif // CEDITOUTBINDSTAB_H
