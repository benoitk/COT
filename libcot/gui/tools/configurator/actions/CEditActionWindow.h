#ifndef CEDITACTIONWINDOW_H
#define CEDITACTIONWINDOW_H

#include "IConfiguratorEditWindow.h"

class CEditActionTab;
class CEditStepListTab;
class IAction;
class CAutomate;
class CEditActionWindow : public IConfiguratorEditWindow
{
    Q_OBJECT

public:
    explicit CEditActionWindow(CAutomate* arg_automate, IAction *action, QWidget *parent = Q_NULLPTR);

protected:
    virtual void applyProperties() Q_DECL_OVERRIDE;

private slots:
    void slotRetranslate();
    void slotOkTriggered();
    void slotCancelTriggered();

private:
    CEditActionTab *m_ceditActionTab;
    CEditStepListTab *m_ceditActionStepsTab;
    IAction * m_action;
    CAutomate* m_automate;
};

#endif // CEDITACTIONWINDOW_H
