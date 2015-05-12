#include "CConfiguratorActionsTab.h"
#include "ConfiguratorActionsUIHandler.h"
#include "ui_CConfiguratorActionsTab.h"
#include "IVariableObjectDescriber.h"
#include "CAutomate.h"

CConfiguratorActionsTab::CConfiguratorActionsTab(QWidget *parent)
    : IConfiguratorTab(parent)
    , ui(new Ui::CConfiguratorActionsTab)
{
    ui->setupUi(this);

    m_iactionUIHandler = new ConfiguratorActionsUIHandler(ui->swCentral, this);
    CVariableIActionDescriber *actionDescriber = new CVariableIActionDescriber(m_iactionUIHandler);
    m_iactionUIHandler->setDescriber(actionDescriber);
    slotUpdateLayout();

    connect(ui->vbbButtons->addAction(CToolButton::Add), &QAction::triggered,
            this, &CConfiguratorActionsTab::slotAddAction);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IConfiguratorTab::backTriggered);
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged,
            this, &CConfiguratorActionsTab::slotUpdateLayout);
}

CConfiguratorActionsTab::~CConfiguratorActionsTab()
{
    delete ui;
}

void CConfiguratorActionsTab::slotAddAction()
{
    QString name;
    if (!m_iactionUIHandler->selectAction(name) || name.isEmpty()) {
        return;
    }
    //TODO cycle block ?
}

void CConfiguratorActionsTab::slotUpdateLayout()
{
    m_iactionUIHandler->layout();
}
