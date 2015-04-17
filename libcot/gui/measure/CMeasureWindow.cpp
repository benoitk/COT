#include "CMeasureWindow.h"
#include "ui_CMeasureWindow.h"
#include "CMeasureStreamTab.h"
#include "CMeasureMeasureTab.h"

CMeasureWindow::CMeasureWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CMeasureWindow)
{
    ui->setupUi(this);
    addTab(new CMeasureStreamTab(this), tr("STREAM 1"));
    addTab(new CMeasureMeasureTab(this), tr("MEASURE 1"));
}

CMeasureWindow::~CMeasureWindow()
{

}

void CMeasureWindow::backTriggered()
{
    close();
}

void CMeasureWindow::addTab(IMeasureTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IMeasureTab::backTriggered, this, &CMeasureWindow::backTriggered);
}
