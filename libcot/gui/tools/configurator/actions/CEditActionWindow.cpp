#include "CEditActionWindow.h"
#include "ui_CEditActionWindow.h"
#include "CEditActionTab.h"

#include <CAutomate.h>
#include <IVariable.h>
#include <IAction.h>

CEditActionWindow::CEditActionWindow(IAction *action, QWidget *parent)
    : QWidget(parent)
    , m_action(action)
    , ui(new Ui::CEditActionWindow)
    , m_ceditActionTab(new CEditActionTab(action, this))
    , m_ceditActionStepsTab(Q_NULLPTR)
{
    ui->setupUi(this);

    addTab(m_ceditActionTab, QString());
    //addTab(m_ceditActionStepsTab, QString());

    retranslate();
}

CEditActionWindow::~CEditActionWindow()
{
    delete ui;
}

void CEditActionWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("General"));
    ui->twPages->setTabText(1, tr("Steps"));
}

void CEditActionWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}

void CEditActionWindow::slotOkTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    // SERES_TODO: add api for IAction serialisation
//    QVariantMap oldData /*= m_action->serialize()*/;
//    oldData[QStringLiteral("related_stream_name")] = m_action->getRelatedStreamName();

    for (int i = 0; i < ui->twPages->count(); i++) {
        IEditActionTab *tab = qobject_cast<IEditActionTab *>(ui->twPages->widget(i));
        tab->applyProperties(m_action);
    }

//    automate->informAboutActionChanges(m_action, oldData);
    close();
}

void CEditActionWindow::slotCancelTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    const bool isNew = !automate->getListActions().contains(m_action);

    if (isNew) {
        delete m_action;
        m_action = Q_NULLPTR;
    }

    close();
}

void CEditActionWindow::addTab(IEditActionTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IEditActionTab::signalOkTriggered, this, &CEditActionWindow::slotOkTriggered);
    connect(tab, &IEditActionTab::signalCancelTriggered, this, &CEditActionWindow::slotCancelTriggered);
}
