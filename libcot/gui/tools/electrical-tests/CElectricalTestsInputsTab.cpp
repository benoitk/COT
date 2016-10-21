#include "CElectricalTestsInputsTab.h"
#include "ui_CElectricalTestsInputsTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsInputsTab::CElectricalTestsInputsTab(CAutomate* arg_automate, QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsInputsTab)
    , m_automate(arg_automate)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);

    m_elecTestInputsHandler = new IVariableUIHandler(arg_automate, ui->swCentral, this);
    updateElecTestInputs();
    connect(arg_automate, &CAutomate::signalDisplayUpdated,
            this, &CElectricalTestsInputsTab::updateElecTestInputs);
}

CElectricalTestsInputsTab::~CElectricalTestsInputsTab()
{
    delete ui;
}

void CElectricalTestsInputsTab::updateElecTestInputs()
{
    CDisplayConf *displayConf = m_automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    m_listInputVar =  screenElecVariables.value(CDisplayConf::STR_ELEC_INPUTS);
    m_elecTestInputsHandler->layout(m_listInputVar);
}


void CElectricalTestsInputsTab::slotUpdateInput(){
    foreach (IVariable* var, m_listInputVar) {
        if(var->getType() == e_type_bool && var->getOrganType() == e_type_organ_input){
            dynamic_cast<IVariableInput*>(var)->readValue();
        }
    }
}
