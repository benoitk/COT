#include "CElectricalTestsRelaysTab.h"
#include "ui_CElectricalTestsRelaysTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsRelaysTab::CElectricalTestsRelaysTab(CAutomate* arg_automate, QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsRelaysTab)
    , m_automate(arg_automate)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);

    m_elecTestRelaysHandler = new IVariableUIHandler(arg_automate, ui->swCentral, this);
    updateElecTestRelays();
    connect(arg_automate, &CAutomate::signalDisplayUpdated,
            this, &CElectricalTestsRelaysTab::updateElecTestRelays);
}

CElectricalTestsRelaysTab::~CElectricalTestsRelaysTab()
{
    delete ui;
}


void CElectricalTestsRelaysTab::updateElecTestRelays()
{
    CDisplayConf *displayConf = m_automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList screenElecRelays =  screenElecVariables.value(CDisplayConf::STR_ELEC_RELAYS);
    m_elecTestRelaysHandler->layout(screenElecRelays);
}
