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
    explicit CPCMeasureTab(QWidget *parent = Q_NULLPTR);
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
    void updateAlarmsAction();
    void slotUpdateControlButtons(CAutomate::eStateAutomate arg_state);

private:
    Ui::CPCMeasureTab *ui;
    IVariableMeasuresUIHandler *m_measuresHandler;
    QHash<QString, CPlotObject *> m_plotObjectHash;
    CPendingAlarms *m_pendingAlarms;
};

#endif // CPCMEASURETAB_H
