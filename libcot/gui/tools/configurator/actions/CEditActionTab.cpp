#include "CEditActionTab.h"
#include "ui_CEditActionTab.h"
#include "CEditActionTabUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <IVariable.h>
#include <IAction.h>

CEditActionTab::CEditActionTab(IAction *action, QWidget *parent)
    : IEditActionTab(parent)
    , ui(new Ui::CEditActionTab)
{
    ui->setupUi(this);
    m_handler = new CEditActionTabUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    m_handler->layout(action);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered, this, &CEditActionTab::signalOkTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered, this, &IEditActionTab::signalCancelTriggered);
}

CEditActionTab::~CEditActionTab()
{
    delete ui;
}

void CEditActionTab::applyProperties(IAction *action)
{
    IVariableObjectDescriber *describer = m_handler->describer();

    // We know hard coded variable names from our describer so just use them.
    // KDAB_TODO
//    action->setName(describer->getVariable(QStringLiteral("name"))->toString());
//    action->setLbl(describer->getVariable(QStringLiteral("label"))->toString());
}
