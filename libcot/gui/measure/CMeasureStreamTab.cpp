#include "CMeasureStreamTab.h"
#include "ui_CMeasureStreamTab.h"
#include "IVariableUIHandler.h"

CMeasureStreamTab::CMeasureStreamTab(CAutomate* arg_automate, const IVariablePtrList &variables, QWidget *parent)
    : IMeasureTab(parent)
    , ui(new Ui::CMeasureStreamTab)
{
    ui->setupUi(this);
    m_variableHandler = new IVariableUIHandler(arg_automate, ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    m_variableHandler->layout(variables);

    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IMeasureTab::backTriggered);
}

CMeasureStreamTab::~CMeasureStreamTab()
{
    delete ui;
}
