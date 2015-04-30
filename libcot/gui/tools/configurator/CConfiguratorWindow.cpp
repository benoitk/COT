#include "CConfiguratorWindow.h"
#include "ui_CConfiguratorWindow.h"
#include "IConfiguratorTab.h"
#include "CConfiguratorCycleTab.h"
#include "CConfiguratorActionsTab.h"
#include "CConfiguratorVariablesTab.h"
#include "CConfiguratorSequencerTab.h"
#include "CConfiguratorStreamsTab.h"
#include "CConfiguratorExtensionsTab.h"
#include "CConfiguratorDisplayTab.h"
#include "CConfiguratorHardwareTab.h"

CConfiguratorWindow::CConfiguratorWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CConfiguratorWindow)
{
    ui->setupUi(this);
    addTab(new CConfiguratorCycleTab(this), tr("Cycles"));
    addTab(new CConfiguratorActionsTab(this), tr("Actions"));
    addTab(new CConfiguratorVariablesTab(this), tr("Variables"));
    addTab(new CConfiguratorSequencerTab(this), tr("Sequencer"));
    addTab(new CConfiguratorStreamsTab(this), tr("Streams / Measures"));
    addTab(new CConfiguratorExtensionsTab(this), tr("Extensions"));
    addTab(new CConfiguratorDisplayTab(this), tr("Display"));
    addTab(new CConfiguratorHardwareTab(this), tr("Hardware"));
}

CConfiguratorWindow::~CConfiguratorWindow()
{
    delete ui;
}

void CConfiguratorWindow::backTriggered()
{
    close();
}

void CConfiguratorWindow::addTab(IConfiguratorTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IConfiguratorTab::backTriggered, this, &CConfiguratorWindow::backTriggered);
}
