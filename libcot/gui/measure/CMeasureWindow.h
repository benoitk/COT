#ifndef CMEASUREWINDOW_H
#define CMEASUREWINDOW_H

#include <QWidget>

namespace Ui {
class CMeasureWindow;
}

class IMeasureTab;
class CVariableStream;
class CAutomate;
class CMeasureWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CMeasureWindow(CAutomate* arg_automate, CVariableStream *stream, QWidget *parent = Q_NULLPTR);
    ~CMeasureWindow();

private slots:
    void backTriggered();

private:
    Ui::CMeasureWindow *ui;
    CAutomate* m_automate;
    void addTab(IMeasureTab *tab, const QString &title);
};

#endif // CMEASUREWINDOW_H
