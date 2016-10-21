#include "CMaintenanceWindow.h"
#include "ui_CMaintenanceWindow.h"
#include "CMaintenanceMaintenanceTab.h"
#include "CMaintenanceDiagnosticTab.h"
#include "CUserSession.h"
#include "CAutomate.h"

//CMaintenanceWindow* CMaintenanceWindow::singleton = 0;

//CMaintenanceWindow* CMaintenanceWindow::getInstance(){
//    if(!singleton)
//        singleton = new CMaintenanceWindow();
//    return singleton;
//}

CMaintenanceWindow::CMaintenanceWindow(CAutomate* arg_automate, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CMaintenanceWindow)
    , m_automate(arg_automate)
{
    ui->setupUi(this);
    addTab(new CMaintenanceMaintenanceTab(m_automate, this), QString());
    addTab(new CMaintenanceDiagnosticTab(m_automate, this), QString());
    connect(ui->twPages, &QTabWidget::currentChanged, m_automate, &CAutomate::slotTabChanged);
    retranslate();
}

CMaintenanceWindow::~CMaintenanceWindow()
{
}
void CMaintenanceWindow::slotUserSessionClosed()
{
//	if(!CUserSession::getInstance()->loginAsLastUser())
//		slotBackTriggered();
    CUserSession::getInstance()->loginAsLastUser(true);
}

void CMaintenanceWindow::slotBackTriggered()
{
    //a l'essais pour ne pas utiliser le slotUserSessionClosed
    CUserSession::getInstance()->loginAsLastUser(true);
    m_automate->exitMaintenanceMode();
    disconnect(CUserSession::getInstance(), 0, this, 0);
    close();
}

void CMaintenanceWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("MAINTENANCE"));
    ui->twPages->setTabText(1, tr("DIAGNOSTIC"));
}

void CMaintenanceWindow::addTab(IMaintenanceTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IMaintenanceTab::backTriggered, this, &CMaintenanceWindow::slotBackTriggered);
}

void CMaintenanceWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}
