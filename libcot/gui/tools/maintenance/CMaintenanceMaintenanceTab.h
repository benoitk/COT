#ifndef CMAINTENANCEMAINTENANCETAB_H
#define CMAINTENANCEMAINTENANCETAB_H

#include "IMaintenanceTab.h"
#include <QList>

class QVBoxLayout;
class CDialogMaintenance;
class CToolButton;
class ICycle;
class CMaintenanceMaintenanceTab : public IMaintenanceTab
{
    Q_OBJECT

public:
    explicit CMaintenanceMaintenanceTab(QWidget *parent = Q_NULLPTR);
    ~CMaintenanceMaintenanceTab();

private:
    CDialogMaintenance* resetDialog();

    QVBoxLayout* m_cyclesLayout;
    QWidget* m_cycleContainerWidget;
    CDialogMaintenance* m_dialog;
    QList<CToolButton*>  m_listButtonsPlay;
    CVerticalButtonBar* m_vbbButtons;
signals:
    void signalStopCycle();
    void signalRunCycle(const QString&);

private slots:
    void slotUpdateLayout();
    void slotStopCycle();
    void slotCycleStopped(const QString&);
    void slotPlayPressed();
    void slotCurrentMaintenanceCycleChanged(const QString &name);


};

#endif // CMAINTENANCEMAINTENANCETAB_H
