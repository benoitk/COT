#ifndef CMAINTENANCEDIAGNOSTICTAB_H
#define CMAINTENANCEDIAGNOSTICTAB_H

#include "IMaintenanceTab.h"

namespace Ui {
class CMaintenanceDiagnosticTab;
}

class CMaintenanceDiagnosticTab : public IMaintenanceTab
{
    Q_OBJECT

public:
    explicit CMaintenanceDiagnosticTab(QWidget *parent = Q_NULLPTR);
    ~CMaintenanceDiagnosticTab();

private:
    Ui::CMaintenanceDiagnosticTab *ui;
};

#endif // CMAINTENANCEDIAGNOSTICTAB_H
