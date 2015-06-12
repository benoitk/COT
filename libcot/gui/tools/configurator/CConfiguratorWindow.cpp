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
#include "CConfiguratorNetworkTab.h"

CConfiguratorWindow::CConfiguratorWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CConfiguratorWindow)
{
    ui->setupUi(this);
    addTab(new CConfiguratorCycleTab(this));
    addTab(new CConfiguratorActionsTab(this));
    addTab(new CConfiguratorVariablesTab(this));
    addTab(new CConfiguratorSequencerTab(this));
    addTab(new CConfiguratorStreamsTab(this));
    addTab(new CConfiguratorExtensionsTab(this));
    addTab(new CConfiguratorDisplayTab(this));
    addTab(new CConfiguratorHardwareTab(this));
    addTab(new CConfiguratorNetworkTab(this));
    slotRetranslate();
}

CConfiguratorWindow::~CConfiguratorWindow()
{
    delete ui;
}

void CConfiguratorWindow::slotRetranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("Cycles"));
    ui->twPages->setTabText(1, tr("Actions"));
    ui->twPages->setTabText(2, tr("Variables"));
    ui->twPages->setTabText(3, tr("Scheduler"));
    ui->twPages->setTabText(4, tr("Streams / Measures"));
    ui->twPages->setTabText(5, tr("Extensions"));
    ui->twPages->setTabText(6, tr("Display"));
    ui->twPages->setTabText(7, tr("Hardware"));
    ui->twPages->setTabText(8, tr("Network"));
}

void CConfiguratorWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);

    if (event->type() == QEvent::LanguageChange) {
        slotRetranslate();
    }
}

void CConfiguratorWindow::slotBackTriggered()
{
    close();
}

void CConfiguratorWindow::addTab(IConfiguratorTab *tab)
{
    ui->twPages->addTab(tab, QString());
    connect(tab, &IConfiguratorTab::backTriggered, this, &CConfiguratorWindow::slotBackTriggered);
}
