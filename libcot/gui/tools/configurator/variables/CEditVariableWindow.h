#ifndef CEDITVARIABLEWINDOW_H
#define CEDITVARIABLEWINDOW_H

#include "IConfiguratorEditWindow.h"

class IVariable;

class CEditVariableWindow : public IConfiguratorEditWindow
{
    Q_OBJECT

public:
    explicit CEditVariableWindow(IVariable *ivar, QWidget *parent = Q_NULLPTR);

private slots:
    void slotRetranslate();
    void slotCancelTriggered();
    void slotOkTriggered();

private:
    IVariable *m_variable;
};

#endif // CEDITVARIABLEWINDOW_H
