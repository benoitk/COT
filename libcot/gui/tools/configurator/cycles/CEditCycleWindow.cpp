#include "CEditCycleWindow.h"
#include "ui_CEditCycleWindow.h"
#include "IEditCycleTab.h"
#include "CEditCycleTab.h"

#include <CAutomate.h>
#include <IVariable.h>
#include <ICycle.h>

CEditCycleWindow::CEditCycleWindow(ICycle *cycle, QWidget *parent)
    : QWidget(parent)
    , m_cycle(cycle)
    , ui(new Ui::CEditCycleWindow)
    , m_ceditCycleTab(new CEditCycleTab(cycle, this))
    , m_ceditCycleStepsTab(Q_NULLPTR)
{
    ui->setupUi(this);

    addTab(m_ceditCycleTab, QString());
    //addTab(m_ceditCycleStepsTab, QString());

    retranslate();
}

CEditCycleWindow::~CEditCycleWindow()
{
    delete ui;
}

void CEditCycleWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("General"));
    ui->twPages->setTabText(1, tr("Steps"));
}

void CEditCycleWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}

void CEditCycleWindow::slotOkTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    // SERES_TODO: add api for ICycle serialisation
    QVariantMap oldData /*= m_cycle->serialize()*/;
    oldData[QStringLiteral("related_stream_name")] = m_cycle->getRelatedStreamName();

    for (int i = 0; i < ui->twPages->count(); ++i) {
        IEditCycleTab *tab = qobject_cast<IEditCycleTab *>(ui->twPages->widget(i));
        tab->applyProperties(m_cycle);
    }

    automate->informAboutCycleChanges(m_cycle, oldData);
    close();
}

void CEditCycleWindow::slotCancelTriggered()
{
    CAutomate *automate = CAutomate::getInstance();
    const bool isNew = !automate->getListCycles().contains(m_cycle);

    if (isNew) {
        delete m_cycle;
        m_cycle = Q_NULLPTR;
    }

    close();
}

void CEditCycleWindow::addTab(IEditCycleTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IEditCycleTab::signalOkTriggered, this, &CEditCycleWindow::slotOkTriggered);
    connect(tab, &IEditCycleTab::signalCancelTriggered, this, &CEditCycleWindow::slotCancelTriggered);
}
