#include "CElectricalTestsActuatorTab.h"
#include "ui_CElectricalTestsActuatorTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsActuatorTab::CElectricalTestsActuatorTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsActuatorTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);

    m_elecTestActuatorHandler = new IVariableUIHandler(ui->swCentral, this);
    updateElecTestActuator();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayUpdated,
            this, &CElectricalTestsActuatorTab::updateElecTestActuator);
}

CElectricalTestsActuatorTab::~CElectricalTestsActuatorTab()
{
    delete ui;
}


void CElectricalTestsActuatorTab::updateElecTestActuator()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList screenElecActuator =  screenElecVariables.value(CDisplayConf::STR_ELEC_ACTUATOR);
    m_elecTestActuatorHandler->layout(screenElecActuator);
}

