#include "CElectricalTestsActuatorTab.h"
#include "ui_CElectricalTestsActuatorTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsActuatorTab::CElectricalTestsActuatorTab(CAutomate* arg_automate, QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsActuatorTab)
    , m_automate(arg_automate)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);

    m_elecTestActuatorHandler = new IVariableUIHandler(arg_automate, ui->swCentral, this);
    updateElecTestActuator();
    connect(arg_automate, &CAutomate::signalDisplayUpdated,
            this, &CElectricalTestsActuatorTab::updateElecTestActuator);
}

CElectricalTestsActuatorTab::~CElectricalTestsActuatorTab()
{
    delete ui;
}


void CElectricalTestsActuatorTab::updateElecTestActuator()
{
    CDisplayConf *displayConf = m_automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList screenElecActuator =  screenElecVariables.value(CDisplayConf::STR_ELEC_ACTUATOR);
    m_elecTestActuatorHandler->layout(screenElecActuator);
}

