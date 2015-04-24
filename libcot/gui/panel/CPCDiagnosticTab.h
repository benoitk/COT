#ifndef CPCDIAGNOSTICTAB_H
#define CPCDIAGNOSTICTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCDiagnosticTab;
}

class IVariableUIHandler;

/**
 * @brief Widget displayed inside the "diagnostic" tab.
 */

class CPCDiagnosticTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCDiagnosticTab(QWidget *parent = Q_NULLPTR);
    ~CPCDiagnosticTab();

protected Q_SLOTS:
    void updateDiagnostic();

private:
    Ui::CPCDiagnosticTab *ui;
    IVariableUIHandler *m_diagnosticHandler;
};

#endif // CPCDIAGNOSTICTAB_H
