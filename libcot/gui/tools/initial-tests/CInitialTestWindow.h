#ifndef CINITIALTESTWINDOW_H
#define CINITIALTESTWINDOW_H

#include <CDialog.h>

#include "cot_global.h"

class IVariableUIHandler;
class LIBCOT_EXPORT CInitialTestsWindow : public CDialog
{
    Q_OBJECT
public:
    explicit CInitialTestsWindow(QWidget *parent = 0);

signals:

public slots:
    void slotBackTriggered();
    void slotUpdateWindow();

private:

    IVariableUIHandler* m_testVarHandler;
    IVariableUIHandler* m_indicatorVarHandler;
};

#endif // CINITIALTESTWINDOW_H
