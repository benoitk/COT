#include "CElectricalTests420Tab.h"
#include "ui_CElectricalTests420Tab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"
#include "CVariableBool.h"

CElectricalTests420Tab::CElectricalTests420Tab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTests420Tab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);

    m_elecTest420Handler = new IVariableUIHandler(ui->swCentral, this);
    updateElecTest420();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayUpdated,
            this, &CElectricalTests420Tab::updateElecTest420);
}

CElectricalTests420Tab::~CElectricalTests420Tab()
{
    delete ui;
}

void CElectricalTests420Tab::updateElecTest420()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList listTmp =  screenElecVariables.value(CDisplayConf::STR_ELEC_420);
    IVariablePtrList screenElec420;
    for(int i=0; i<listTmp.count();++i){
        if(listTmp.at(i)->getType() == e_type_bool){
            m_listBtTests.append(dynamic_cast<CVariableBool*>(listTmp.at(i)));
            connect(listTmp.at(i), SIGNAL(signalVariableChanged(IVariable*)), this, SLOT(slotOneOfBtTestsClicked(IVariable*)) );
        }
        if((i+1)%5 != 0){
            screenElec420.append(listTmp.at(i));

        }
        m_mapVar.insert(listTmp.at(i)->getName(), listTmp.at(i));
    }
    m_elecTest420Handler->layout(screenElec420);
}

void CElectricalTests420Tab::slotOneOfBtTestsClicked(IVariable * arg_var){
    if(arg_var->toBool()){
        foreach (CVariableBool* var, m_listBtTests) {
            if(var != arg_var)
            var->setValue(false);
        }
        if(arg_var->getName() == "var_test4mA_1")
            m_mapVar.value("var_loop1_4_20_data")->setValue(m_mapVar.value("var_loop1_4_20_min")->toInt());
       else if(arg_var->getName() == "var_test20mA_1")
            m_mapVar.value("var_loop1_4_20_data")->setValue(m_mapVar.value("var_loop1_4_20_max")->toInt());

        else if(arg_var->getName() == "var_test4mA_2")
            m_mapVar.value("var_loop2_4_20_data")->setValue(m_mapVar.value("var_loop2_4_20_min")->toInt());
       else if(arg_var->getName() == "var_test20mA_2")
            m_mapVar.value("var_loop2_4_20_data")->setValue(m_mapVar.value("var_loop2_4_20_max")->toInt());


    }
}
