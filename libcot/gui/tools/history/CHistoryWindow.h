#ifndef CHISTORYWINDOW_H
#define CHISTORYWINDOW_H

#include <QWidget>

namespace Ui {
class CHistoryWindow;
}
class IVariableUIHandler;

class CHistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CHistoryWindow(QWidget *parent = Q_NULLPTR);
    ~CHistoryWindow();

protected Q_SLOTS:
    void updateHistory();

private slots:
    void backTriggered();

private:
    Ui::CHistoryWindow *ui;
    IVariableUIHandler *m_historyHandler;

};

#endif // CHISTORYWINDOW_H
