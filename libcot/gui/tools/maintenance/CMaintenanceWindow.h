#ifndef CMAINTENANCEWINDOW_H
#define CMAINTENANCEWINDOW_H

#include <QWidget>

namespace Ui {
class CMaintenanceWindow;
}

class IMaintenanceTab;

class CMaintenanceWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CMaintenanceWindow(QWidget *parent = Q_NULLPTR);
    ~CMaintenanceWindow();

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void backTriggered();

private:
    Ui::CMaintenanceWindow *ui;

    void addTab(IMaintenanceTab *tab, const QString &title);
};

#endif // CMAINTENANCEWINDOW_H
