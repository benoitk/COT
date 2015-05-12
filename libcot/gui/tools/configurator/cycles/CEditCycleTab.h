#ifndef CEDITCYCLETAB_H
#define CEDITCYCLETAB_H

#include "IEditCycleTab.h"

namespace Ui {
class CEditCycleTab;
}

class CEditCycleTabUIHandler;
class ICycle;

class CEditCycleTab : public IEditCycleTab
{
    Q_OBJECT

public:
    explicit CEditCycleTab(ICycle *cycle, QWidget *parent = Q_NULLPTR);
    ~CEditCycleTab();

    void applyProperties(ICycle *cycle) Q_DECL_OVERRIDE;

private:
    Ui::CEditCycleTab *ui;
    CEditCycleTabUIHandler *m_handler;
};

#endif // CEDITCYCLETAB_H
