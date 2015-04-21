#include "CLogFilesWindow.h"
#include "ui_CLogFilesWindow.h"

CLogFilesWindow::CLogFilesWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CLogFilesWindow)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &CLogFilesWindow::backTriggered);
}

CLogFilesWindow::~CLogFilesWindow()
{
    delete ui;
}

void CLogFilesWindow::backTriggered()
{
    close();
}
