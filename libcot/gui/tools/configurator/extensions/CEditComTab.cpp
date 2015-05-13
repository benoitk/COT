#include "CEditComTab.h"
#include "ui_CEditComTab.h"
#include "CAutomate.h"

CEditComTab::CEditComTab(QWidget *parent)
    : IEditExtensionTab(parent)
    , ui(new Ui::CEditComTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &IEditExtensionTab::signalCancelTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Ok), &QAction::triggered,
            this, &IEditExtensionTab::signalOkTriggered);

}

CEditComTab::~CEditComTab()
{
    delete ui;
}

void CEditComTab::applyProperties(IVariable *ivar)
{

}
