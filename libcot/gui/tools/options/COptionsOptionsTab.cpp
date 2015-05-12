#include "COptionsOptionsTab.h"
#include "ui_COptionsOptionsTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

COptionsOptionsTab::COptionsOptionsTab(QWidget *parent)
    : IOptionsTab(parent)
    , ui(new Ui::COptionsOptionsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IOptionsTab::backTriggered);

    m_optionHandler = new IVariableUIHandler(ui->swCentral, this);
    updateOptions();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayUpdated,
            this, &COptionsOptionsTab::updateOptions);
}

COptionsOptionsTab::~COptionsOptionsTab()
{
    delete ui;
}

void COptionsOptionsTab::updateOptions()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    IVariablePtrList screenOptions = displayConf->getListForScreenOptions();
    m_optionHandler->layout(screenOptions);
}
