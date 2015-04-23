#include "CMeasureMeasureTab.h"
#include "ui_CMeasureMeasureTab.h"
#include "IVariableUIHandler.h"

CMeasureMeasureTab::CMeasureMeasureTab(const QStringList &variables, QWidget *parent)
    : IMeasureTab(parent)
    , ui(new Ui::CMeasureMeasureTab)
{
    ui->setupUi(this);
    m_variableHandler = new IVariableUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    m_variableHandler->layout(variables);

    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &IMeasureTab::backTriggered);
}

CMeasureMeasureTab::~CMeasureMeasureTab()
{
    delete ui;
}
