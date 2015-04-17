#include "CElectricalTestsWindow.h"
#include "ui_CElectricalTestsWindow.h"
#include "CElectricalTestsPumpsTab.h"
#include "CElectricalTestsRelaysTab.h"
#include "CElectricalTestsActuatorTab.h"
#include "CElectricalTests420Tab.h"
#include "CElectricalTestsInputsTab.h"

CElectricalTestsWindow::CElectricalTestsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CElectricalTestsWindow)
{
    ui->setupUi(this);
    addTab(new CElectricalTestsPumpsTab(this), tr("PUMPS"));
    addTab(new CElectricalTestsRelaysTab(this), tr("RELAYS"));
    addTab(new CElectricalTestsActuatorTab(this), tr("ACTUATOR"));
    addTab(new CElectricalTests420Tab(this), tr("4-20mA OUTPUT"));
    addTab(new CElectricalTestsInputsTab(this), tr("INPUTS"));
}

CElectricalTestsWindow::~CElectricalTestsWindow()
{
    delete ui;
}

void CElectricalTestsWindow::backTriggered()
{
    close();
}

void CElectricalTestsWindow::addTab(IElectricalTestsTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IElectricalTestsTab::backTriggered, this, &CElectricalTestsWindow::backTriggered);
}
