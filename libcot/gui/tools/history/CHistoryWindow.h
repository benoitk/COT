#ifndef CHISTORYWINDOW_H
#define CHISTORYWINDOW_H

#include <QWidget>

namespace Ui {
class CHistoryWindow;
}

class QTextDocument;
class CAutomate;
class CHistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CHistoryWindow(CAutomate* arg_automate, QTextDocument *document, QWidget *parent = Q_NULLPTR);
    ~CHistoryWindow();

private:
    Ui::CHistoryWindow *ui;
    CAutomate* m_automate;

private slots:
    void backTriggered();
    void slotVariableChanged(const QString &name);
};

#endif // CHISTORYWINDOW_H
