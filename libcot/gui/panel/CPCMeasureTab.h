#ifndef CPCMEASURETAB_H
#define CPCMEASURETAB_H

#include "IPCTab.h"
#include "CAutomate.h"

namespace Ui {
class CPCMeasureTab;
}

class IVariableMeasuresUIHandler;
class CPendingAlarms;
class CPlotObject;

class CPCMeasureTab : public IPCTab
{
    Q_OBJECT
public:
    explicit CPCMeasureTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CPCMeasureTab();

    CVerticalButtonBar *buttonBar() const Q_DECL_OVERRIDE;

private slots:
    void slotAlarmsTriggered();
    void slotPlayStopTriggered();
    void slotStopTriggered();
    void slotStopEndCycleTriggered();
    void slotNextStreamTriggered();
    void slotUpdateStreamsMeasures();
    void slotVariableChanged(const QString &name, const QDateTime &dateTime);
    void slotUpdatePlotting();
    void slotUpdateAlarmsAction();
    void slotUpdatePlayStopButton(bool arg_running, const QString& runningCycleName);
    void slotUpdateStopEndCycleButton(bool arg_stopEndCycle,const QString& runningCycleName);

private:
    Ui::CPCMeasureTab *ui;
    IVariableMeasuresUIHandler *m_measuresHandler;
    QHash<QString, CPlotObject *> m_plotObjectHash;
    CPendingAlarms *m_pendingAlarms;
};

#endif // CPCMEASURETAB_H
