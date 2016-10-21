#ifndef CEDITVARIABLEWINDOW_H
#define CEDITVARIABLEWINDOW_H

#include "IConfiguratorEditWindow.h"

class IVariable;
class CAutomate;
class CEditVariableWindow : public IConfiguratorEditWindow
{
    Q_OBJECT

public:
    explicit CEditVariableWindow(CAutomate* arg_automate, IVariable *ivar, QWidget *parent = Q_NULLPTR);

private slots:
    void slotRetranslate();
    void slotCancelTriggered();
    void slotOkTriggered();

private:
    IVariable *m_variable;
    CAutomate* m_automate;
};

#endif // CEDITVARIABLEWINDOW_H
