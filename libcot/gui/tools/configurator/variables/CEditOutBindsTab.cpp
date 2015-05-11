#include "CEditOutBindsTab.h"
#include "ui_CEditOutBindsTab.h"
#include "CAutomate.h"
#include <IConfiguratorUIHandler.h>

CEditOutBindsTab::CEditOutBindsTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditOutBindsTab)
{
    ui->setupUi(this);
    m_configuratorUIHandler = new IConfiguratorUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &IEditVariableTab::cancelTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &IEditVariableTab::okTriggered);
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

