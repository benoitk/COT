#include "CElectricalTestsPumpsTab.h"
#include "ui_CElectricalTestsPumpsTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsPumpsTab::CElectricalTestsPumpsTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsPumpsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);


    m_elecTestPumpHandler = new IVariableUIHandler(ui->swCentral, this);
    updateElecTestPump();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayChanged,
            this, &CElectricalTestsPumpsTab::updateElecTestPump);
}

CElectricalTestsPumpsTab::~CElectricalTestsPumpsTab()
{
    delete ui;
}

void CElectricalTestsPumpsTab::updateElecTestPump()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList screenElecPump = screenElecVariables.value(CDisplayConf::STR_ELEC_PUMP);
    m_elecTestPumpHandler->layout(screenElecPump);
}
