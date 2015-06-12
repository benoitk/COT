#ifndef CSTATUSWIDGET_H
#define CSTATUSWIDGET_H

#include <QWidget>

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

private:
    Ui::CStatusWidget *ui;
};

#endif // CSTATUSWIDGET_H
