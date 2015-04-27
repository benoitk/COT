#ifndef CMAINTENANCEDIAGNOSTICTAB_H
#define CMAINTENANCEDIAGNOSTICTAB_H

#include "IMaintenanceTab.h"

namespace Ui {
class CMaintenanceDiagnosticTab;
}

class IVariableUIHandler;

class CMaintenanceDiagnosticTab : public IMaintenanceTab
{
    Q_OBJECT

public:
    explicit CMaintenanceDiagnosticTab(QWidget *parent = Q_NULLPTR);
    ~CMaintenanceDiagnosticTab();

private:
    Ui::CMaintenanceDiagnosticTab *ui;
    IVariableUIHandler *m_diagnosticHandler;

private slots:
    void slotUpdateLayout();
};

#endif // CMAINTENANCEDIAGNOSTICTAB_H
