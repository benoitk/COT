#include "CElectricalTestsRelaysTab.h"
#include "ui_CElectricalTestsRelaysTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CElectricalTestsRelaysTab::CElectricalTestsRelaysTab(QWidget *parent)
    : IElectricalTestsTab(parent)
    , ui(new Ui::CElectricalTestsRelaysTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IElectricalTestsTab::backTriggered);

    m_elecTestRelaysHandler = new IVariableUIHandler(ui->swCentral, this);
    updateElecTestRelays();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayconfChanged,
            this, &CElectricalTestsRelaysTab::updateElecTestRelays);
}

CElectricalTestsRelaysTab::~CElectricalTestsRelaysTab()
{
    delete ui;
}


void CElectricalTestsRelaysTab::updateElecTestRelays()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    QMap<QString, QList<IVariable*> > screenElecVariables = displayConf->getMapForScreenElectricalTests();
    IVariablePtrList screenElecRelays =  screenElecVariables.value(CDisplayConf::strElecRelays);
    m_elecTestRelaysHandler->layout(screenElecRelays);
}
