#ifndef CEDITACTIONWINDOW_H
#define CEDITACTIONWINDOW_H

#include "IConfiguratorEditWindow.h"

class CEditActionTab;
class CEditActionStepsTab;
class IAction;

class CEditActionWindow : public IConfiguratorEditWindow
{
    Q_OBJECT

public:
    explicit CEditActionWindow(IAction *action, QWidget *parent = Q_NULLPTR);

private slots:
    void slotRetranslate();
    void slotOkTriggered();
    void slotCancelTriggered();

private:
    CEditActionTab *m_ceditActionTab;
    CEditActionStepsTab *m_ceditActionStepsTab;
};

#endif // CEDITACTIONWINDOW_H
