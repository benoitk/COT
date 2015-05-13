#include "CEditVariableWindow.h"
#include "ui_CEditVariableWindow.h"
#include "IEditVariableTab.h"
#include "CEditInBindsTab.h"
#include "CEditOutBindsTab.h"
#include "CEditVariableTab.h"
#include "CAutomate.h"
#include <IVariable.h>

CEditVariableWindow::CEditVariableWindow(IVariable *ivar, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CEditVariableWindow)
    , m_ivariable(ivar)
{
    ui->setupUi(this);
    m_ceditVariableTab = new CEditVariableTab(this);
    m_ceditOutBindsTab = new CEditOutBindsTab(this);
    m_ceditInBindsTab = new CEditInBindsTab(this);

    addTab(m_ceditVariableTab, QString());
    addTab(m_ceditOutBindsTab, QString());
    addTab(m_ceditInBindsTab, QString());
    retranslate();
    if (ivar) {
        setVariables(ivar);
    }
}

CEditVariableWindow::~CEditVariableWindow()
{
    delete ui;
}

void CEditVariableWindow::setVariables(IVariable *ivar)
{
    m_ceditVariableTab->setVariables(ivar);
    m_ceditOutBindsTab->setVariables(ivar);
    m_ceditInBindsTab->setVariables(ivar);
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


void CEditVariableWindow::slotCancelTriggered()
{
    //TODO save variable ?
    close();
}


void CEditVariableWindow::slotOkTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    for (int i = 0; i < ui->twPages->count(); ++i) {
        IEditVariableTab *tab = qobject_cast<IEditVariableTab *>(ui->twPages->widget(i));
        tab->applyProperties(m_ivariable);
    }
    //TODO implement it.
    //automate->informAboutVariableChanges(m_ivariable, oldmap);
    close();
}

void CEditVariableWindow::addTab(IEditVariableTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IEditVariableTab::signalCancelTriggered, this, &CEditVariableWindow::slotCancelTriggered);
    connect(tab, &IEditVariableTab::signalOkTriggered, this, &CEditVariableWindow::slotOkTriggered);
}
