#include "COptionsWindow.h"
#include "ui_COptionsWindow.h"
#include "COptionsOptionsTab.h"
#include "COptionsAutoCyclesTab.h"
#include "COptionsThresholdTab.h"
#include "COptionsDateTimeTab.h"
#include <CConfiguratorSequencerTab.h>
#include "CAutomate.h"

COptionsWindow::COptionsWindow(CAutomate* arg_automate, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::COptionsWindow)
    , m_automate(arg_automate)
{
    ui->setupUi(this);
    addTab(new COptionsOptionsTab(arg_automate, this), tr("OPTIONS"));
 //   addTab(new COptionsAutoCyclesTab(this), tr("AUTO. CYCLES"));
 //   addTab(new CConfiguratorSequencerTab(this), tr("SCHEDULER"));
 //   addTab(new COptionsThresholdTab(this), tr("THRESHOLD"));
    addTab(new COptionsDateTimeTab(this), tr("DATE/TIME"));
}

COptionsWindow::~COptionsWindow()
{
    delete ui;
}

void COptionsWindow::backTriggered()
{
    m_automate->slotSerializeAndSave();
    close();
}

void COptionsWindow::addTab(QWidget *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    // could be &IOptionsTab::backTriggered or &IConfiguratorTab::backTriggered so we use SIGNAL()
    connect(tab, SIGNAL(backTriggered()), this, SLOT(backTriggered()));
}
