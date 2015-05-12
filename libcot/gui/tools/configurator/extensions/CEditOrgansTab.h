#ifndef CEDITORGANSTAB_H
#define CEDITORGANSTAB_H

#include "IEditExtensionTab.h"
namespace Ui {
class CEditOrgansTab;
}
class CEditOrgansTab : public IEditExtensionTab
{
    Q_OBJECT
public:
    explicit CEditOrgansTab(QWidget *parent = Q_NULLPTR);
    ~CEditOrgansTab();

private:
    Ui::CEditOrgansTab *ui;
};

#endif // CEDITORGANSTAB_H
