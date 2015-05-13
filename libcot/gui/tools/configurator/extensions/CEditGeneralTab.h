#ifndef CEDITGENERALTAB_H
#define CEDITGENERALTAB_H

#include "IEditExtensionTab.h"
namespace Ui {
class CEditGeneralTab;
}
class CEditGeneralTab : public IEditExtensionTab
{
    Q_OBJECT
public:
    explicit CEditGeneralTab(QWidget *parent = Q_NULLPTR);
    ~CEditGeneralTab();
    void applyProperties(IVariable *ivar) Q_DECL_OVERRIDE;
private:
    Ui::CEditGeneralTab *ui;
};

#endif // CEDITGENERALTAB_H
