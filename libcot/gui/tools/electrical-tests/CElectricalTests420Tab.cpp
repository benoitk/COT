#include "CElectricalTests420Tab.h"
#include "ui_CElectricalTests420Tab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

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
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayconfChanged,
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
    IVariablePtrList screenElec420 =  screenElecVariables.value(CDisplayConf::strElec420);
    m_elecTest420Handler->layout(screenElec420);
}
