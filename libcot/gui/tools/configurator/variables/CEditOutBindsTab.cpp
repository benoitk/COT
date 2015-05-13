#include "CEditOutBindsTab.h"
#include "ui_CEditOutBindsTab.h"
#include "CAutomate.h"
#include "CEditOutBindsUIHandler.h"

CEditOutBindsTab::CEditOutBindsTab(QWidget *parent)
    : IEditVariableTab(parent)
    , ui(new Ui::CEditOutBindsTab)
{
    ui->setupUi(this);
    m_configuratorUIHandler = new CEditOutBindsUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &IEditVariableTab::signalCancelTriggered);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &IEditVariableTab::signalOkTriggered);
}

CEditOutBindsTab::~CEditOutBindsTab()
{
    delete ui;
}

void CEditOutBindsTab::setVariables(IVariable *ivar)
{
    Q_ASSERT(ivar);
    const QList<IVariable *> listOutBinds = ivar->getListOutBinds();
    m_configuratorUIHandler->layout(listOutBinds, true);
}

void CEditOutBindsTab::applyProperties(IVariable *ivar)
{

}

