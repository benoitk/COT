#include "CElectricalTestsSolenoidsTab.h"
#include "ui_CElectricalTestsSolenoidsTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsSolenoidsTab::CElectricalTestsSolenoidsTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsSolenoidsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);

    m_elecTestRelaysHandler = new IVariableUIHandler(ui->swCentral, this);
    updateElecTestRelays();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayUpdated,
            this, &CElectricalTestsSolenoidsTab::updateElecTestRelays);
}

CElectricalTestsSolenoidsTab::~CElectricalTestsSolenoidsTab()
{
    delete ui;
}


void CElectricalTestsSolenoidsTab::updateElecTestRelays()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList screenElecRelays =  screenElecVariables.value(CDisplayConf::STR_ELEC_SOLENOIDS);
    m_elecTestRelaysHandler->layout(screenElecRelays);
}
