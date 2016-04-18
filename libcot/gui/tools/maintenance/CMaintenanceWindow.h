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
public :
    static CMaintenanceWindow* getInstance();
private:
    explicit CMaintenanceWindow();
    ~CMaintenanceWindow();
    static CMaintenanceWindow* singleton;
public slots:
    void retranslate();
    void slotUserSessionClosed();


protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slotBackTriggered();

private:
    Ui::CMaintenanceWindow *ui;

    void addTab(IMaintenanceTab *tab, const QString &title);
};

#endif // CMAINTENANCEWINDOW_H
