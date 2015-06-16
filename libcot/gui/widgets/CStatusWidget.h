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
    void slotUpdateCurrentStream(int stream, const QString &label);
    void slotUpdateCurrentStep(float step, const QString &label);

private:
    Ui::CStatusWidget *ui;
};

#endif // CSTATUSWIDGET_H
