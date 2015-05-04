#ifndef CEDITVARIABLETAB_H
#define CEDITVARIABLETAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditVariableTab;
}
class CEditVariableTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditVariableTab(QWidget *parent = Q_NULLPTR);
    ~CEditVariableTab();
private:
    Ui::CEditVariableTab *ui;
};

#endif // CEDITVARIABLETAB_H
