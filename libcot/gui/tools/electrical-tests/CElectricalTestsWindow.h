#ifndef CELECTRICALTESTSWINDOW_H
#define CELECTRICALTESTSWINDOW_H

#include <QWidget>

namespace Ui {
class CElectricalTestsWindow;
}

class IElectricalTestsTab;

class CElectricalTestsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CElectricalTestsWindow(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsWindow();

private slots:
    void backTriggered();

private:
    Ui::CElectricalTestsWindow *ui;

    void addTab(IElectricalTestsTab *tab, const QString &title);
};

#endif // CELECTRICALTESTSWINDOW_H
