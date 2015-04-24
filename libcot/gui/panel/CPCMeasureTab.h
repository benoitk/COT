#ifndef CPCMEASURETAB_H
#define CPCMEASURETAB_H

#include "IPCTab.h"

namespace Ui {
class CPCMeasureTab;
}

class IVariableMeasuresUIHandler;

class CPCMeasureTab : public IPCTab
{
    Q_OBJECT
public:
    explicit CPCMeasureTab(QWidget *parent = Q_NULLPTR);
    ~CPCMeasureTab();

private slots:
    void slotAlarmsTriggered();
    void slotPlayTriggered();
    void slotStopTriggered();
    void slotStopEndCycleTriggered();
    void slotNextStreamTriggered();
    void slotUpdateStreamsMeasures();
    void slotUpdateAlarmsIcon(const QString &name);

private:
    Ui::CPCMeasureTab *ui;
    IVariableMeasuresUIHandler *m_measuresHandler;
};

#endif // CPCMEASURETAB_H
