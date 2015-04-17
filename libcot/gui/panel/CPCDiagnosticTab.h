#ifndef CPCDIAGNOSTICTAB_H
#define CPCDIAGNOSTICTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCDiagnosticTab;
}

class CPCDiagnosticTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCDiagnosticTab(QWidget *parent = Q_NULLPTR);
    ~CPCDiagnosticTab();

private:
    Ui::CPCDiagnosticTab *ui;
};

#endif // CPCDIAGNOSTICTAB_H
