#ifndef CEDITCYCLETAB_H
#define CEDITCYCLETAB_H

#include "IEditCycleTab.h"

namespace Ui {
class CEditCycleTab;
}

class CEditCycleTabUIHandler;
class ICycle;

typedef QPair<QString, ICycle *> CyclePair; // Stream Name, ICycle

class CEditCycleTab : public IEditCycleTab
{
    Q_OBJECT

public:
    explicit CEditCycleTab(const CyclePair &cyclePair, QWidget *parent = Q_NULLPTR);
    ~CEditCycleTab();

protected slots:
    void slotOkTriggered();

private:
    Ui::CEditCycleTab *ui;
    CEditCycleTabUIHandler *m_handler;
};

#endif // CEDITCYCLETAB_H
