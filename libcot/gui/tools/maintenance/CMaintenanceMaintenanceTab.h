#ifndef CMAINTENANCEMAINTENANCETAB_H
#define CMAINTENANCEMAINTENANCETAB_H

#include "IMaintenanceTab.h"

namespace Ui {
class CMaintenanceMaintenanceTab;
}

class IVariableUIHandler;

class CMaintenanceMaintenanceTab : public IMaintenanceTab
{
    Q_OBJECT

public:
    explicit CMaintenanceMaintenanceTab(QWidget *parent = Q_NULLPTR);
    ~CMaintenanceMaintenanceTab();

private:
    Ui::CMaintenanceMaintenanceTab *ui;
    IVariableUIHandler *m_variableHandler;

private slots:
    void slotUpdateLayout();
};

#endif // CMAINTENANCEMAINTENANCETAB_H
