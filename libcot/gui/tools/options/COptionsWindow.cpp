#include "COptionsWindow.h"
#include "ui_COptionsWindow.h"
#include "COptionsOptionsTab.h"
#include "COptionsAutoCyclesTab.h"
#include "COptionsSchedulerTab.h"
#include "COptionsThresholdTab.h"
#include "COptionsDateTimeTab.h"

COptionsWindow::COptionsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::COptionsWindow)
{
    ui->setupUi(this);
    addTab(new COptionsOptionsTab(this), tr("OPTIONS"));
    addTab(new COptionsAutoCyclesTab(this), tr("AUTO. CYCLES"));
    addTab(new COptionsSchedulerTab(this), tr("SCHEDULER"));
    addTab(new COptionsThresholdTab(this), tr("THRESHOLD"));
    addTab(new COptionsDateTimeTab(this), tr("DATE/TIME"));
}

COptionsWindow::~COptionsWindow()
{
    delete ui;
}

void COptionsWindow::backTriggered()
{
    close();
}

void COptionsWindow::addTab(IOptionsTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IOptionsTab::backTriggered, this, &COptionsWindow::backTriggered);
}
