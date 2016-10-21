#include "CElectricalTestsPumpsTab.h"
#include "ui_CElectricalTestsPumpsTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsPumpsTab::CElectricalTestsPumpsTab(CAutomate* arg_automate, QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsPumpsTab)
    , m_automate(arg_automate)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);


    m_elecTestPumpHandler = new IVariableUIHandler(arg_automate, ui->swCentral, this);
    updateElecTestPump();
    connect(arg_automate, &CAutomate::signalDisplayUpdated,
            this, &CElectricalTestsPumpsTab::updateElecTestPump);
}

CElectricalTestsPumpsTab::~CElectricalTestsPumpsTab()
{
    delete ui;
}

void CElectricalTestsPumpsTab::updateElecTestPump()
{
    CDisplayConf *displayConf = m_automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList screenElecPump = screenElecVariables.value(CDisplayConf::STR_ELEC_PUMP);
    m_elecTestPumpHandler->layout(screenElecPump);
}
