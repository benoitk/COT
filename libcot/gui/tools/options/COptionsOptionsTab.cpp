#include "COptionsOptionsTab.h"
#include "ui_COptionsOptionsTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

COptionsOptionsTab::COptionsOptionsTab(CAutomate* arg_automate, QWidget *parent)
    : IOptionsTab(parent)
    , m_automate(arg_automate)
    , ui(new Ui::COptionsOptionsTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IOptionsTab::backTriggered);

    m_optionHandler = new IVariableUIHandler(arg_automate, ui->swCentral, this);
    updateOptions();
    connect(arg_automate, &CAutomate::signalDisplayUpdated,
            this, &COptionsOptionsTab::updateOptions);
}

COptionsOptionsTab::~COptionsOptionsTab()
{
    delete ui;
}

void COptionsOptionsTab::updateOptions()
{
    CDisplayConf *displayConf = m_automate->getDisplayConf();
    IVariablePtrList screenOptions = displayConf->getListForScreenOptions();
    m_optionHandler->layout(screenOptions);
}
