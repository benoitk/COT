#include "CEditCycleTab.h"
#include "ui_CEditCycleTab.h"
#include "CEditCycleTabUIHandler.h"

CEditCycleTab::CEditCycleTab(const CyclePair &cyclePair, QWidget *parent)
    : IEditCycleTab(parent)
    , ui(new Ui::CEditCycleTab)
{
    ui->setupUi(this);
    m_handler = new CEditCycleTabUIHandler(ui->swCentral, this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    m_handler->layout(cyclePair);

    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered, this, &CEditCycleTab::slotOkTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered, this, &IEditCycleTab::backTriggered);
}

CEditCycleTab::~CEditCycleTab()
{
    delete ui;
}

void CEditCycleTab::slotOkTriggered()
{
    //
}
