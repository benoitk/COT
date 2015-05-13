#ifndef CEDITVARIABLEWINDOW_H
#define CEDITVARIABLEWINDOW_H

#include "IConfiguratorEditWindow.h"

class IVariable;
class CEditVariableTab;
class CEditOutBindsTab;
class CEditInBindsTab;

class CEditVariableWindow : public IConfiguratorEditWindow
{
    Q_OBJECT

public:
    explicit CEditVariableWindow(IVariable *ivar, QWidget *parent = Q_NULLPTR);

    void setVariables(IVariable *ivar);

private slots:
    void slotRetranslate();
    void slotCancelTriggered();
    void slotOkTriggered();

private:
    CEditVariableTab *m_ceditVariableTab;
    CEditOutBindsTab *m_ceditOutBindsTab;
    CEditInBindsTab *m_ceditInBindsTab;
};

#endif // CEDITVARIABLEWINDOW_H
