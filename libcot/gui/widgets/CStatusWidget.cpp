#include "CStatusWidget.h"
#include "ui_CStatusWidget.h"

CStatusWidget::CStatusWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CStatusWidget)
{
    ui->setupUi(this);
}

CStatusWidget::~CStatusWidget()
{
    delete ui;
}
