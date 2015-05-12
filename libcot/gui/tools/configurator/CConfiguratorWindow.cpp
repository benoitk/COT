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
    addTab(new CConfiguratorCycleTab(this), QString());
    addTab(new CConfiguratorActionsTab(this), QString());
    addTab(new CConfiguratorVariablesTab(this), QString());
    addTab(new CConfiguratorSequencerTab(this), QString());
    addTab(new CConfiguratorStreamsTab(this), QString());
    addTab(new CConfiguratorExtensionsTab(this), QString());
    addTab(new CConfiguratorDisplayTab(this), QString());
    addTab(new CConfiguratorHardwareTab(this), QString());
    addTab(new CConfiguratorNetworkTab(this), QString());
    retranslate();
}

CConfiguratorWindow::~CConfiguratorWindow()
{
    delete ui;
}


void CConfiguratorWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("Cycles"));
    ui->twPages->setTabText(1, tr("Actions"));
    ui->twPages->setTabText(2, tr("Variables"));
    ui->twPages->setTabText(3, tr("Sequencer"));
    ui->twPages->setTabText(4, tr("Streams / Measures"));
    ui->twPages->setTabText(5, tr("Extensions"));
    ui->twPages->setTabText(6, tr("Display"));
    ui->twPages->setTabText(7, tr("Hardware"));
    ui->twPages->setTabText(8, tr("Network"));
}

void CConfiguratorWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}


void CConfiguratorWindow::backTriggered()
{
    close();
}

void CConfiguratorWindow::addTab(IConfiguratorTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IConfiguratorTab::signalBackTriggered, this, &CConfiguratorWindow::backTriggered);
}
