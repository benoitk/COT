#include "CEditVariableWindow.h"
#include "ui_CEditVariableWindow.h"
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

CEditvariableWindow::CEditvariableWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CEditVariableWindow)
{
    ui->setupUi(this);
    retranslate();
}

CEditvariableWindow::~CEditvariableWindow()
{
    delete ui;
}


void CEditvariableWindow::retranslate()
{
    ui->retranslateUi(this);
}

void CEditvariableWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}


void CEditvariableWindow::backTriggered()
{
    close();
}

void CEditvariableWindow::addTab(IConfiguratorTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IConfiguratorTab::backTriggered, this, &CEditvariableWindow::backTriggered);
}
