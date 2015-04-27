#include "CElectricalTestsInputsTab.h"
#include "ui_CElectricalTestsInputsTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsInputsTab::CElectricalTestsInputsTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsInputsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);

    m_elecTestInputsHandler = new IVariableUIHandler(ui->swCentral, this);
    updateElecTestInputs();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayChanged,
            this, &CElectricalTestsInputsTab::updateElecTestInputs);
}

CElectricalTestsInputsTab::~CElectricalTestsInputsTab()
{
    delete ui;
}

void CElectricalTestsInputsTab::updateElecTestInputs()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList screenElecInputs =  screenElecVariables.value(CDisplayConf::STR_ELEC_INPUTS);
    m_elecTestInputsHandler->layout(screenElecInputs);
}
