#ifndef CPCMEASURETAB_H
#define CPCMEASURETAB_H

#include "IPCTab.h"

namespace Ui {
class CPCMeasureTab;
}

class IVariableMeasuresUIHandler;
class CPendingAlarms;

class CPCMeasureTab : public IPCTab
{
    Q_OBJECT
public:
    explicit CPCMeasureTab(QWidget *parent = Q_NULLPTR);
    ~CPCMeasureTab();

    CVerticalButtonBar *buttonBar() const Q_DECL_OVERRIDE;

private slots:
    void slotAlarmsTriggered();
    void slotPlayTriggered();
    void slotStopTriggered();
    void slotStopEndCycleTriggered();
    void slotNextStreamTriggered();
    void slotUpdateStreamsMeasures();
    void slotUpdateAlarms(int id, const QDateTime &dateTime, const QString &description);
    void slotUpdatePlotting(const QString &name);
    void updateAlarmsAction();

private:

    Ui::CPCMeasureTab *ui;
    IVariableMeasuresUIHandler *m_measuresHandler;
    CPendingAlarms *m_pendingAlarms;
};

#endif // CPCMEASURETAB_H
