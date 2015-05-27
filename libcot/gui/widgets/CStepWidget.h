#ifndef CSTEPWIDGET_H
#define CSTEPWIDGET_H

#include <QGroupBox>

class CStep;
class IAction;
class CStepWidgetUIHandler;
class IScrollableUIWidget;
class CVariableCStepDescriber;

class QLabel;

class CStepWidget : public QGroupBox
{
    Q_OBJECT

public:
    CStepWidget(CStep *step, QWidget *parent = Q_NULLPTR);

    bool isStopStep() const;
    void editStep();
    CStep *createNewStep() const;

private:
    QLabel *m_interval;
    IScrollableUIWidget *m_scrollable;
    CStepWidgetUIHandler *m_handler;
    CVariableCStepDescriber *m_stepDescriber;

    QString getLabel() const;
    float getInterval() const;
    QList<IAction *> getActions() const;

private slots:
    void slotUpdateInfos(bool emitSignal);
    void slotUpdateInfosWithSignal();
    void slotAddTriggered();
    void slotEditTriggered();

signals:
    void signalStepChanged();
};

#endif // CSTEPWIDGET_H
