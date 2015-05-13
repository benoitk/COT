#ifndef CEDITCOMTAB_H
#define CEDITCOMTAB_H

#include "IEditExtensionTab.h"
namespace Ui {
class CEditComTab;
}
class CEditComTab : public IEditExtensionTab
{
    Q_OBJECT
public:
    explicit CEditComTab(QWidget *parent = Q_NULLPTR);
    ~CEditComTab();
    void applyProperties(IVariable *ivar) Q_DECL_OVERRIDE;

private:
    Ui::CEditComTab *ui;
};

#endif // CEDITCOMTAB_H
