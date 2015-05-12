#include "CEditInBindsTab.h"
#include "ui_CEditInBindsTab.h"
#include "CAutomate.h"
#include <IConfiguratorUIHandler.h>

CEditInBindsTab::CEditInBindsTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditInBindsTab)
{
    ui->setupUi(this);
    m_configuratorUIHandler = new IConfiguratorUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &IEditVariableTab::backTriggered);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &IEditVariableTab::okTriggered);
}

CEditInBindsTab::~CEditInBindsTab()
{
    delete ui;
}

void CEditInBindsTab::setVariables(IVariable *ivar)
{
    Q_ASSERT(ivar);
    const QList<IVariable *> listInBinds = ivar->getListInBinds();
    m_configuratorUIHandler->layout(listInBinds);
}

void CEditInBindsTab::applyProperties(IVariable *ivar)
{

}

