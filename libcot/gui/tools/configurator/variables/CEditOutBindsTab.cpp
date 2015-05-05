#include "CEditOutBindsTab.h"
#include "ui_CEditOutBindsTab.h"
#include "CAutomate.h"
#include <ConfiguratorUIHandler.h>

CEditOutBindsTab::CEditOutBindsTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditOutBindsTab)
{
    ui->setupUi(this);
    m_configuratorUIHandler = new ConfiguratorUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IEditVariableTab::backTriggered);
}

CEditOutBindsTab::~CEditOutBindsTab()
{
    delete ui;
}

void CEditOutBindsTab::setVariables(const QString &variableName)
{
    IVariable *ivar = CAutomate::getInstance()->getVariable(variableName);
    Q_ASSERT(ivar);
    const QList<IVariable *> listOutBinds = ivar->getListOutBinds();
    m_configuratorUIHandler->layout(listOutBinds, true);
}

