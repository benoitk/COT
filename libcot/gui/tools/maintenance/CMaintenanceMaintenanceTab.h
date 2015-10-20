#ifndef CMAINTENANCEMAINTENANCETAB_H
#define CMAINTENANCEMAINTENANCETAB_H

#include "IMaintenanceTab.h"
#include <QList>

class QVBoxLayout;
class CDialogMaintenance;
class CToolButton;
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
    QList<CToolButton*>  m_listButtonsPlay;

signals:
    void signalStopCycle();
    void signalRunCycle();

private slots:
    void slotUpdateLayout();
    void slotStopCycle();
    void slotCycleStopped();
    void slotPlayPressed();
    void slotCurrentMaintenanceCycleChanged(const QString &name);
};

#endif // CMAINTENANCEMAINTENANCETAB_H
