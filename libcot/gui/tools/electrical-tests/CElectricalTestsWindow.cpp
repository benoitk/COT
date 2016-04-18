#include "CElectricalTestsWindow.h"
#include "ui_CElectricalTestsWindow.h"
#include "CElectricalTestsPumpsTab.h"
#include "CElectricalTestsRelaysTab.h"
#include "CElectricalTestsActuatorTab.h"
#include "CElectricalTests420Tab.h"
#include "CElectricalTestsInputsTab.h"
#include "CElectricalTestsSolenoidsTab.h"
#include "CUserSession.h"

#include <qtimer.h>

CElectricalTestsWindow::CElectricalTestsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CElectricalTestsWindow)
{
    m_timerInput = Q_NULLPTR;
    ui->setupUi(this);
    addTab(new CElectricalTestsPumpsTab(this), tr("PUMPS"));
    addTab(new CElectricalTestsRelaysTab(this), tr("RELAYS"));
    addTab(new CElectricalTestsSolenoidsTab(this), tr("SOLENOIDS"));
    addTab(new CElectricalTestsActuatorTab(this), tr("ACTUATOR"));
    addTab(new CElectricalTests420Tab(this), tr("4-20mA OUTPUT"));
    addTab(new CElectricalTestsInputsTab(this), tr("INPUTS"));

    connect(ui->twPages, &QTabWidget::currentChanged, this, &CElectricalTestsWindow::slotTabChanged);

}
void CElectricalTestsWindow::slotTabChanged(int index){
    if(ui->twPages->tabText(index) == tr("INPUTS")){
        if(!m_timerInput){
            m_timerInput = new QTimer();
            m_timerInput->setInterval(1000);
            CElectricalTestsInputsTab* widget = dynamic_cast<CElectricalTestsInputsTab*>(ui->twPages->widget(index));
            connect(m_timerInput, &QTimer::timeout, widget, &CElectricalTestsInputsTab::slotUpdateInput);
        }
        m_timerInput->start(1000);
    }
    else if(m_timerInput) m_timerInput->stop();
}

CElectricalTestsWindow::~CElectricalTestsWindow()
{
    delete ui;
}

void CElectricalTestsWindow::backTriggered()
{
    //a l'essais pour ne pas utiliser le slotUserSessionClosed
    CUserSession::getInstance()->loginAsLastUser(true);
    if(m_timerInput) m_timerInput->stop();
    close();
}

void CElectricalTestsWindow::addTab(IElectricalTestsTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IElectricalTestsTab::backTriggered, this, &CElectricalTestsWindow::backTriggered);
}
