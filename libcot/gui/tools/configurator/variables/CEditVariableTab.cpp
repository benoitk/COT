#include "CEditVariableTab.h"
#include "ui_CEditVariableTab.h"
#include "CAutomate.h"
#include "CEditVariableTabUIHandler.h"
#include <IConfiguratorUIHandler.h>
#include <IVariableObjectDescriber.h>

CEditVariableTab::CEditVariableTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditVariableTab)
{
    ui->setupUi(this);
    m_configuratorUIHandler = new CEditVariableTabUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &IEditVariableTab::signalCancelTriggered);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &IEditVariableTab::signalOkTriggered);
}

CEditVariableTab::~CEditVariableTab()
{
    delete ui;
}

void CEditVariableTab::setVariables(IVariable *ivar)
{
    m_configuratorUIHandler->layout(ivar);
}

void CEditVariableTab::applyProperties(IVariable *ivar)
{
    IVariableObjectDescriber *describer = m_configuratorUIHandler->describer();
    ivar->setName(describer->getVariable(QStringLiteral("name"))->toString());
    ivar->setLabel(describer->getVariable(QStringLiteral("label"))->toString());
    //TODO add type/unit
}

