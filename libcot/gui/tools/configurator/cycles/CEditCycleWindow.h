#ifndef CEDITCYCLEWINDOW_H
#define CEDITCYCLEWINDOW_H

#include "IConfiguratorEditWindow.h"

class ICycle;
class CEditCycleTab;
class CEditStepListTab;

class CEditCycleWindow : public IConfiguratorEditWindow
{
    Q_OBJECT

public:
    explicit CEditCycleWindow(ICycle *cycle, QWidget *parent = Q_NULLPTR);

private slots:
    void slotRetranslate();
    void slotOkTriggered();
    void slotCancelTriggered();

private:
    CEditCycleTab *m_ceditCycleTab;
    CEditStepListTab *m_ceditCycleStepListTab;
    ICycle * m_cycle;
};

#endif // CEDITCYCLEWINDOW_H
