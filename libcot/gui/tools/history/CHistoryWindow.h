#ifndef CHISTORYWINDOW_H
#define CHISTORYWINDOW_H

#include <QWidget>

namespace Ui {
class CHistoryWindow;
}

class CHistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CHistoryWindow(QWidget *parent = Q_NULLPTR);
    ~CHistoryWindow();

private slots:
    void backTriggered();

private:
    Ui::CHistoryWindow *ui;
};

#endif // CHISTORYWINDOW_H
