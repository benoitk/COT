#include "CEditVariableWindow.h"
#include "ui_CEditVariableWindow.h"
#include "IEditVariableTab.h"
#include "CEditInBindsTab.h"
#include "CEditOutBindsTab.h"
#include "CEditVariableTab.h"

#include <IVariable.h>

CEditvariableWindow::CEditvariableWindow(const QString &variableName, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CEditVariableWindow)
{
    ui->setupUi(this);
    m_ceditVariableTab = new CEditVariableTab(this);
    m_ceditOutBindsTab = new CEditOutBindsTab(this);
    m_ceditInBindsTab = new CEditInBindsTab(this);

    addTab(m_ceditVariableTab, QString());
    addTab(m_ceditOutBindsTab, QString());
    addTab(m_ceditInBindsTab, QString());
    retranslate();
    if (!variableName.isEmpty()) {
        setVariables(variableName);
    }
}

CEditvariableWindow::~CEditvariableWindow()
{
    delete ui;
}

void CEditvariableWindow::setVariables(const QString &name)
{
    m_ceditVariableTab->setVariables(name);
    m_ceditOutBindsTab->setVariables(name);
    m_ceditInBindsTab->setVariables(name);
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
    //TODO save variable ?
    close();
}

void CEditvariableWindow::addTab(IEditVariableTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IEditVariableTab::backTriggered, this, &CEditvariableWindow::backTriggered);
}
