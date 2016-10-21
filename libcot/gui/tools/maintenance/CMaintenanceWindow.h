#ifndef CMAINTENANCEWINDOW_H
#define CMAINTENANCEWINDOW_H

#include <QWidget>

namespace Ui {
class CMaintenanceWindow;
}

class IMaintenanceTab;
class CAutomate;
class CMaintenanceWindow : public QWidget
{
    Q_OBJECT
public :
    explicit CMaintenanceWindow(CAutomate* arg_automate, QWidget* parent);
    ~CMaintenanceWindow();

//    static CMaintenanceWindow* getInstance();
private:
//    static CMaintenanceWindow* singleton;
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
    CAutomate* m_automate;
};

#endif // CMAINTENANCEWINDOW_H
