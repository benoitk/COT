#ifndef CHISTORYWINDOW_H
#define CHISTORYWINDOW_H

#include <QWidget>

namespace Ui {
class CHistoryWindow;
}

class QTextDocument;

class CHistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CHistoryWindow(QTextDocument *history, QWidget *parent = Q_NULLPTR);
    ~CHistoryWindow();

private:
    Ui::CHistoryWindow *ui;

private slots:
    void backTriggered();
    void slotVariableChanged(const QString &name);
};

#endif // CHISTORYWINDOW_H
