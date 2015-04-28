#ifndef CMAINTENANCEMAINTENANCETAB_H
#define CMAINTENANCEMAINTENANCETAB_H

#include "IMaintenanceTab.h"

namespace Ui {
class CMaintenanceMaintenanceTab;
}

class IVariableMaintenanceUIHandler;

class CMaintenanceMaintenanceTab : public IMaintenanceTab
{
    Q_OBJECT

public:
    explicit CMaintenanceMaintenanceTab(QWidget *parent = Q_NULLPTR);
    ~CMaintenanceMaintenanceTab();

private:
    Ui::CMaintenanceMaintenanceTab *ui;
    IVariableMaintenanceUIHandler *m_variableHandler;

private slots:
    void slotUpdateLayout();
    void slotCurrentMaintenanceCycleChanged(const QString &name);
};

#endif // CMAINTENANCEMAINTENANCETAB_H
