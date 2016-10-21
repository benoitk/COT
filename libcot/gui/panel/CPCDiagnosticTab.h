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
    explicit CPCDiagnosticTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CPCDiagnosticTab();

    CVerticalButtonBar *buttonBar() const Q_DECL_OVERRIDE;

protected slots:
    void updateDiagnostic();

private:
    Ui::CPCDiagnosticTab *ui;
    IVariableUIHandler *m_diagnosticHandler;
};

#endif // CPCDIAGNOSTICTAB_H
