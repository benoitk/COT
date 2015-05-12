#include "CEditCycleTab.h"
#include "ui_CEditCycleTab.h"
#include "CEditCycleTabUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <IVariable.h>

CEditCycleTab::CEditCycleTab(ICycle *cycle, QWidget *parent)
    : IEditCycleTab(parent)
    , ui(new Ui::CEditCycleTab)
{
    ui->setupUi(this);
    m_handler = new CEditCycleTabUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    m_handler->layout(cycle);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered, this, &CEditCycleTab::signalOkTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered, this, &IEditCycleTab::signalCancelTriggered);
}

CEditCycleTab::~CEditCycleTab()
{
    delete ui;
}

void CEditCycleTab::applyProperties(ICycle *cycle)
{
    // TODO: Customer do automate internal change handling.
    IVariableObjectDescriber *describer = m_handler->describer();

    // We known hard coded variable names from our describer so just use them.
    cycle->setName(describer->getVariable(QStringLiteral("name"))->toString());
    cycle->setLbl(describer->getVariable(QStringLiteral("label"))->toString());
    //cycle->setType(eTypeCycle(describer->getVariable(QStringLiteral("type"))->toInt())); // read only
    //cycle->setTimer(describer->getVariable(QStringLiteral("timer"))->toInt()); // no customer api
    cycle->setRelatedStreamName(describer->getVariable(QStringLiteral("stream"))->toString());
}
