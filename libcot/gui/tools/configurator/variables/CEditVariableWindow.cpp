#include "CEditVariableWindow.h"
#include "ui_CEditVariableWindow.h"
#include "IEditVariableTab.h"
#include "CEditInBindsTab.h"
#include "CEditOutBindsTab.h"
#include "CEditVariableTab.h"

CEditvariableWindow::CEditvariableWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CEditVariableWindow)
{
    ui->setupUi(this);
    addTab(new CEditVariableTab(this), QString());
    addTab(new CEditOutBindsTab(this), QString());
    addTab(new CEditInBindsTab(this), QString());
    retranslate();
}

CEditvariableWindow::~CEditvariableWindow()
{
    delete ui;
}

void CEditvariableWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("Variables"));
    ui->twPages->setTabText(1, tr("Out Binds"));
    ui->twPages->setTabText(2, tr("In Binds"));
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
