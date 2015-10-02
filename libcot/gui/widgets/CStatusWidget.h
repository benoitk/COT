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
    void slotUpdateStateAutomate(CAutomate::eStateAutomate state);
    void slotAddAlarm(const QString& arg_default);
    void slotRemoveAlarm(const QString& arg_default);
    void slotCleanDefaults();
    void slotUpdateCurrentStream(int stream, const QString &label);
    void slotUpdateCurrentStep(float step, const QString &label);
    void slotUpdateCurrentAction(const QString &label);
    void slotUpdateCountStep(int stepCount);

private:
    Ui::CStatusWidget *ui;

    QString m_lblInfoStep;
};

#endif // CSTATUSWIDGET_H
