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

    bool isSelected() const;
    void setSelected(bool selected);

    float getInterval() const;
    void setInterval(float value);

    bool isStopStep() const;
    void editStep();
    CStep *createNewStep() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QLabel *m_interval;
    IScrollableUIWidget *m_scrollable;
    CStepWidgetUIHandler *m_handler;
    CVariableCStepDescriber *m_stepDescriber;
    bool m_selected;

    QString getLabel() const;
    QList<IAction *> getActions() const;

private slots:
    void slotUpdateInfos(bool emitSignal);
    void slotUpdateInfosWithSignal();
    void slotAddTriggered();
    void slotEditTriggered();

signals:
    void signalStepChanged(float from, float to);
    void signalDeleteRequested();
};

#endif // CSTEPWIDGET_H
