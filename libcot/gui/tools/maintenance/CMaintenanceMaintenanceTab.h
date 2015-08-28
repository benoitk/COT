#ifndef CMAINTENANCEMAINTENANCETAB_H
#define CMAINTENANCEMAINTENANCETAB_H

#include "IMaintenanceTab.h"

class QVBoxLayout;
class CDialogMaintenance;
class CMaintenanceMaintenanceTab : public IMaintenanceTab
{
    Q_OBJECT

public:
    explicit CMaintenanceMaintenanceTab(QWidget *parent = Q_NULLPTR);
    ~CMaintenanceMaintenanceTab();

private:
    QVBoxLayout* m_cyclesLayout;
    QWidget* m_cycleContainerWidget;
    CDialogMaintenance* m_dialog;

signals:
    void signalStopCycle();

private slots:
    void slotUpdateLayout();
    void slotStopCycle();
    void slotCycleStopped();
    void slotPlayPressed();
    void slotCurrentMaintenanceCycleChanged(const QString &name);
};

#endif // CMAINTENANCEMAINTENANCETAB_H
