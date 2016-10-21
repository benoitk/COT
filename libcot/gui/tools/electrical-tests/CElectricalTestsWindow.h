#ifndef CELECTRICALTESTSWINDOW_H
#define CELECTRICALTESTSWINDOW_H

#include <QWidget>

namespace Ui {
class CElectricalTestsWindow;
}

class IElectricalTestsTab;
class CAutomate;
class CElectricalTestsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CElectricalTestsWindow(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsWindow();

private slots:
    void backTriggered();
    void slotTabChanged(int index);
private:
    Ui::CElectricalTestsWindow *ui;
    QTimer* m_timerInput;
    void addTab(IElectricalTestsTab *tab, const QString &title);
};

#endif // CELECTRICALTESTSWINDOW_H
