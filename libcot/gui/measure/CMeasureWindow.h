#ifndef CMEASUREWINDOW_H
#define CMEASUREWINDOW_H

#include <QWidget>

namespace Ui {
class CMeasureWindow;
}

class IMeasureTab;

class CMeasureWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CMeasureWindow(const QString &stream, QWidget *parent = Q_NULLPTR);
    ~CMeasureWindow();

private slots:
    void backTriggered();

private:
    Ui::CMeasureWindow *ui;

    void addTab(IMeasureTab *tab, const QString &title);
};

#endif // CMEASUREWINDOW_H