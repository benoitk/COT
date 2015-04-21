#include "CHistoryWindow.h"
#include "ui_CHistoryWindow.h"

CHistoryWindow::CHistoryWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CHistoryWindow)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &CHistoryWindow::backTriggered);
}

CHistoryWindow::~CHistoryWindow()
{
    delete ui;
}

void CHistoryWindow::backTriggered()
{
    close();
}
