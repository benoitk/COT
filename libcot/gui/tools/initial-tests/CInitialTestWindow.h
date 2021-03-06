#ifndef CINITIALTESTWINDOW_H
#define CINITIALTESTWINDOW_H

#include <CDialog.h>
#include "QTimer"

#include "cot_global.h"

class IVariableUIHandler;
class QAction;
class CAutomate;
class LIBCOT_EXPORT CInitialTestsWindow : public CDialog
{
    Q_OBJECT
public:
    explicit CInitialTestsWindow(CAutomate* arg_automate, QWidget *parent = 0);

signals:

public slots:
    void slotBackTriggered();
    void slotUpdateWindow();

private slots:
    void slotTests();

private:

    IVariableUIHandler* m_testVarHandler;
    IVariableUIHandler* m_indicatorVarHandler;

    QAction* m_actBack;
    QTimer m_timerTests;
    CAutomate* m_automate;
};

#endif // CINITIALTESTWINDOW_H
