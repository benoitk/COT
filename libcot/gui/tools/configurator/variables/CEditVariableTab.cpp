#include "CEditVariableTab.h"
#include "ui_CEditVariableTab.h"
#include "CAutomate.h"
#include "CEditVariableTabUIHandler.h"
#include <IConfiguratorUIHandler.h>

CEditVariableTab::CEditVariableTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditVariableTab)
{
    ui->setupUi(this);
    m_configuratorUIHandler = new CEditVariableTabUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &IEditVariableTab::cancelTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &IEditVariableTab::okTriggered);
}

CEditVariableTab::~CEditVariableTab()
{
    delete ui;
}

void CEditVariableTab::setVariables(const QString &variableName)
{
    IVariable *ivar = CAutomate::getInstance()->getVariable(variableName);
    Q_ASSERT(ivar);

    //m_configuratorUIHandler->layout(variables);
}

