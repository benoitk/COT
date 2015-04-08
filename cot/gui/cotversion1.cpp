#include "cotversion1.h"
#include "ui_cotversion1.h"

COTVersion1::COTVersion1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::COTVersion1)
{
    ui->setupUi(this);
}

COTVersion1::~COTVersion1()
{
    delete ui;
}
