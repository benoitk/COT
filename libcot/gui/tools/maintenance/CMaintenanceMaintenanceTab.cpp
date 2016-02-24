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
#include "CScheduler.h"

CMaintenanceMaintenanceTab::CMaintenanceMaintenanceTab(QWidget *parent)
    : IMaintenanceTab(parent), m_cyclesLayout(Q_NULLPTR), m_cycleContainerWidget(Q_NULLPTR), m_dialog(Q_NULLPTR)
{

    m_isStoppedByIHM = false;
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* leftLayout = new QVBoxLayout;
    m_vbbButtons = new CVerticalButtonBar(this);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(m_vbbButtons);

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
    connect(m_vbbButtons->addAction(CToolButton::Stop), &QAction::triggered, this, &CMaintenanceMaintenanceTab::signalBtStopCyclePressed);
    connect(m_vbbButtons->addAction(CToolButton::Back), &QAction::triggered, this, &IMaintenanceTab::backTriggered);



    m_vbbButtons->button(CToolButton::Stop)->setEnabled(false);
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
        m_listButtonsPlay.append(buttonPlay);
        buttonPlay->setFixedSize(StyleRepository::playStopButtonSize());
        buttonPlay->setCheckable(true);
        buttonPlay->setUserData(cycle->getName());
        connect(buttonPlay, &CToolButton::clicked, this, &CMaintenanceMaintenanceTab::slotPlayPressed);
        //connect(this, &CMaintenanceMaintenanceTab::signalRunCycle, CScheduler::getInstance(), &CScheduler::slotPlayMaintenance);
        row->addWidget(buttonPlay);

        row->addSpacing(200);
        m_cyclesLayout->addLayout(row);
    }
    m_cycleContainerWidget->ensurePolished();

}

void CMaintenanceMaintenanceTab::slotPlayPressed(){
    bool bRunCycle = true;
    m_isStoppedByIHM = false;


    CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString cycleName = button->userData().toString();
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(cycleName); //ne pas spécifier le type dans getCycle, au cas ou on une maintenance est à faire avec un cycle normale

    if(!cycle->isRunning()){
        if(cycle->getType() == e_cycle_maintenance){
            resetDialog();
            CCycleMaintenance* cycleMaintenance = dynamic_cast<CCycleMaintenance*>(cycle);
            if(cycleMaintenance->getListVariablesInput().count() > 0){
                m_dialog->slotUpdateLayout(cycleMaintenance->getListVariablesInput());
                m_dialog->setTitle(tr("Calibration value (") + cycle->getLabel() + ")");
                bRunCycle = m_dialog->exec();
            }
        }
        if(bRunCycle && CAutomate::getInstance()->requestPlayMaintenance(cycleName)) {
            foreach(CToolButton* bt, m_listButtonsPlay){
                if(bt != button){
                    bt->setEnabled(false);
                }else{
                    bt->setChecked(true);
                }
            }

            connect(this, &CMaintenanceMaintenanceTab::signalBtStopCyclePressed, this,  &CMaintenanceMaintenanceTab::slotBtStopCyclePressed);
            connect(CScheduler::getInstance(), &CScheduler::signalCycleIsStopped,
                    this, &CMaintenanceMaintenanceTab::slotCycleStopped);

            m_vbbButtons->button(CToolButton::Back)->setEnabled(false);
            m_vbbButtons->button(CToolButton::Stop)->setEnabled(true);


            //emit signalRunCycle(cycleName);
        }
        else
            button->setChecked(false);
    }

}
CDialogMaintenance* CMaintenanceMaintenanceTab::resetDialog(){
    if(!m_dialog) m_dialog = new CDialogMaintenance(this);
    m_dialog->setDisabledValidationButton(false);
    m_dialog->setErrors(QList<IVariable*>());
}

void CMaintenanceMaintenanceTab::slotCycleStopped(const QString& arg_cycleName){
    ICycle * cycle = CAutomate::getInstance()->getCycle(arg_cycleName);

    disconnect(cycle, 0, this, 0);
    disconnect(this, 0, cycle, 0);
    disconnect(this, &CMaintenanceMaintenanceTab::signalBtStopCyclePressed, this,  &CMaintenanceMaintenanceTab::slotBtStopCyclePressed);
    disconnect(CScheduler::getInstance(), &CScheduler::signalCycleIsStopped,
               this, &CMaintenanceMaintenanceTab::slotCycleStopped);
    bool bTest = CAutomate::getInstance()->isCycleStoppeByAlarm();
    if(!bTest){
        if(cycle->getType() == e_cycle_maintenance){
            resetDialog();
            CCycleMaintenance* cycleMaintenance = dynamic_cast<CCycleMaintenance*>(cycle);
            if(cycleMaintenance->getListVariablesOutput().count() > 0){
                m_dialog->slotUpdateLayout(cycleMaintenance->getListVariablesOutput());
                m_dialog->setTitle(tr("End of calibration (") + cycle->getLabel() + ")");
                if(cycleMaintenance->finishedWithErrors()){
                    m_dialog->setErrors(cycleMaintenance->getListVariablesDefault());
                    m_dialog->setDisabledValidationButton(true);
                }
                else
                    m_dialog->setDisabledValidationButton(false);

                if(!m_isStoppedByIHM && m_dialog->exec()) cycleMaintenance->doValidationCopies();
            }

        }
    }

    foreach(CToolButton* bt, m_listButtonsPlay){
        bt->setEnabled(true);
        bt->setChecked(false);
    }
    m_vbbButtons->button(CToolButton::Back)->setEnabled(true);
    m_vbbButtons->button(CToolButton::Stop)->setEnabled(false);
}

void CMaintenanceMaintenanceTab::slotBtStopCyclePressed(){
    m_isStoppedByIHM = true;
    CScheduler::getInstance()->slotRequestStopSequence();
}

void CMaintenanceMaintenanceTab::slotCurrentMaintenanceCycleChanged(const QString &name)
{
    CAutomate *automate = CAutomate::getInstance();
    ICycle *cycle = automate->getCycle(name, e_cycle_maintenance);

}
