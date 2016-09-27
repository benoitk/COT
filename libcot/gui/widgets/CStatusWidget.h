#ifndef CSTATUSWIDGET_H
#define CSTATUSWIDGET_H

#include <QWidget>
#include <CAutomate.h>

namespace Ui {
class CStatusWidget;
}

class CStatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CStatusWidget(QWidget *parent = Q_NULLPTR);
    ~CStatusWidget();

private Q_SLOTS:
    void slotTimeChanged();

    void slotUpdateStateRunning(bool);
    void slotUpdateStateRunningWillStioEndCycle(bool);
    void slotUpdateStateCurrentCyclePaused(bool);
    void slotUpdateStateRunningAutoCalibration(bool);
    void slotUpdateStateRunningAutoBlank(bool);
    void slotUpdateStateInMaintenance(bool);
    void slotUpdateStateWaiting(bool);

    void slotAddAlarm(const QString& arg_default);
    void slotRemoveAlarm(const QString& arg_default);
    void slotCleanDefaults();
    void slotUpdateCurrentStream(int stream, const QString &label);
    void slotUpdateCurrentStep(float step, const QString &label);
    void slotUpdateNumStep(float step);
    void slotUpdateCurrentAction(const QString &label);
    void slotUpdateCountStep(int stepCount);

private:

    void setStateAutomate(QString state);
    Ui::CStatusWidget *ui;

    QString m_lblInfoStep;
    int m_stepCount;
};

#endif // CSTATUSWIDGET_H
