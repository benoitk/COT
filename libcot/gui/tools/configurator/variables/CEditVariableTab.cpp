#include "CEditVariableTab.h"
#include "ui_CEditVariableTab.h"
#include "CAutomate.h"
#include <ConfiguratorUIHandler.h>

CEditVariableTab::CEditVariableTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditVariableTab)
{
    ui->setupUi(this);
    m_configuratorUIHandler = new ConfiguratorUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IEditVariableTab::backTriggered);
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

