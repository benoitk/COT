#include "CMaintenanceMaintenanceTab.h"
#include "ui_CMaintenanceMaintenanceTab.h"
#include "IVariableMaintenanceUIHandler.h"
#include "CAutomate.h"
#include "CCycleMaintenance.h"
#include "CScheduler.h"
#include "ICycle.h"
#include "CStatusWidget.h"
#include "qlayout.h"
#include "StyleRepository.h"
#include "CDialogMaintenance.h"

CMaintenanceMaintenanceTab::CMaintenanceMaintenanceTab(QWidget *parent)
    : IMaintenanceTab(parent), m_cyclesLayout(Q_NULLPTR), m_cycleContainerWidget(Q_NULLPTR), m_dialog(Q_NULLPTR)
{


    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* leftLayout = new QVBoxLayout;
    CVerticalButtonBar* vbbButtons = new CVerticalButtonBar(this);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(vbbButtons);

    m_cycleContainerWidget = new QWidget(this);
    slotUpdateLayout();
    CStatusWidget* stepWidget = new CStatusWidget(this);
    leftLayout->addStretch();
    leftLayout->addWidget(m_cycleContainerWidget);
    leftLayout->addStretch();
    leftLayout->addWidget(stepWidget);

    CAutomate *automate = CAutomate::getInstance();

    connect(automate, &CAutomate::signalCyclesUpdated, this, &CMaintenanceMaintenanceTab::slotUpdateLayout);
    connect(automate, &CAutomate::signalCurrentMaintenanceCycleChanged, this, &CMaintenanceMaintenanceTab::slotCurrentMaintenanceCycleChanged);
    connect(vbbButtons->addAction(CToolButton::Stop), &QAction::triggered, this, &CMaintenanceMaintenanceTab::signalStopCycle);
    connect(vbbButtons->addAction(CToolButton::Back), &QAction::triggered, this, &IMaintenanceTab::backTriggered);
}

CMaintenanceMaintenanceTab::~CMaintenanceMaintenanceTab()
{

}

void CMaintenanceMaintenanceTab::slotUpdateLayout()
{
    if(m_cyclesLayout) delete m_cyclesLayout;
    m_cyclesLayout = new QVBoxLayout(m_cycleContainerWidget);
    foreach(ICycle* cycle, CAutomate::getInstance()->getScheduler()->getListCyclesMaintenances()){
        QHBoxLayout* row = new QHBoxLayout;

        QLabel* label = new QLabel(cycle->getLabel());
        label->setFont(StyleRepository::measureFont());
        row->addWidget(label);
        row->addStretch();


        CToolButton *buttonPlay = new CToolButton(CToolButton::Play, m_cycleContainerWidget);
        buttonPlay->setFixedSize(StyleRepository::playStopButtonSize());
        buttonPlay->setCheckable(true);
        buttonPlay->setUserData(cycle->getName());
        connect(buttonPlay, &CToolButton::clicked, this, &CMaintenanceMaintenanceTab::slotPlayPressed);

        row->addWidget(buttonPlay);

        row->addSpacing(200);
        m_cyclesLayout->addLayout(row);
    }
    m_cycleContainerWidget->ensurePolished();

}

void CMaintenanceMaintenanceTab::slotPlayPressed(){
    bool bRunCycle = true;
    const CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString cycleName = button->userData().toString();
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(cycleName); //ne pas spécifier le type dans getCycle, au cas ou on une maintenance est à faire avec un cycle normale

    if(cycle->getType() == CYCLE_MAINTENANCE){
        if(!m_dialog) m_dialog = new CDialogMaintenance(this);
        CCycleMaintenance* cycleMaintenance = dynamic_cast<CCycleMaintenance*>(cycle);
        if(cycleMaintenance->getListVariablesInput().count() > 0){
            m_dialog->slotUpdateLayout(cycleMaintenance->getListVariablesInput());
            m_dialog->setTitle(tr("Valeurs étalon (") + cycle->getLabel() + ")");
            bRunCycle = m_dialog->exec();
        }
    }
    connect(cycle, &ICycle::signalStopped, this, &CMaintenanceMaintenanceTab::slotCycleStopped);
    connect(cycle, &ICycle::signalReadyForPlayNextCycle, this, &CMaintenanceMaintenanceTab::slotCycleStopped);
    connect(this, &CMaintenanceMaintenanceTab::signalStopCycle, cycle, &ICycle::slotStopCycle);
    if(bRunCycle) cycle->slotRunCycle();

}

void CMaintenanceMaintenanceTab::slotCycleStopped(){
    ICycle *cycle = qobject_cast<ICycle*>(sender());
    disconnect(cycle, 0, this, 0);
    disconnect(this, 0, cycle, 0);

    if(cycle->getType() == CYCLE_MAINTENANCE){
        if(!m_dialog) m_dialog = new CDialogMaintenance(this);
        CCycleMaintenance* cycleMaintenance = dynamic_cast<CCycleMaintenance*>(cycle);
        if(cycleMaintenance->getListVariablesOutput().count() > 0){
            m_dialog->slotUpdateLayout(cycleMaintenance->getListVariablesOutput());
            m_dialog->setTitle(tr("Fin étalonnage (") + cycle->getLabel() + ")");
            if(m_dialog->exec()) cycleMaintenance->doValidationCopies();
        }

    }
}

void CMaintenanceMaintenanceTab::slotStopCycle(){

}

void CMaintenanceMaintenanceTab::slotCurrentMaintenanceCycleChanged(const QString &name)
{
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(name, CYCLE_MAINTENANCE);

}
