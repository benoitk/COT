#include "CEditVariableWindow.h"
#include "ui_CEditVariableWindow.h"
#include "IEditVariableTab.h"
#include "CEditInBindsTab.h"
#include "CEditOutBindsTab.h"
#include "CEditVariableTab.h"

#include <IVariable.h>

CEditVariableWindow::CEditVariableWindow(const QString &variableName, QWidget *parent)
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

CEditVariableWindow::~CEditVariableWindow()
{
    delete ui;
}

void CEditVariableWindow::setVariables(const QString &name)
{
    m_ceditVariableTab->setVariables(name);
    m_ceditOutBindsTab->setVariables(name);
    m_ceditInBindsTab->setVariables(name);
}

void CEditVariableWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("Variables"));
    ui->twPages->setTabText(1, tr("Out Binds"));
    ui->twPages->setTabText(2, tr("In Binds"));
}

void CEditVariableWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}


void CEditVariableWindow::cancelTriggered()
{
    //TODO save variable ?
    close();
}

void CEditVariableWindow::addTab(IEditVariableTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IEditVariableTab::cancelTriggered, this, &CEditVariableWindow::cancelTriggered);
    //Connect Ok ?
}
