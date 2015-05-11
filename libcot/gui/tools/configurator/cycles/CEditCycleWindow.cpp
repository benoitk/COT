#include "CEditCycleWindow.h"
#include "ui_CEditCycleWindow.h"
#include "IEditCycleTab.h"
#include "CEditCycleTab.h"

#include <IVariable.h>

CEditCycleWindow::CEditCycleWindow(const CyclePair &cyclePair, QWidget *parent)
    : QWidget(parent)
    , m_cyclePair(cyclePair)
    , ui(new Ui::CEditCycleWindow)
    , m_ceditCycleTab(new CEditCycleTab(cyclePair, this))
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


void CEditCycleWindow::backTriggered()
{
    close();
}

void CEditCycleWindow::addTab(IEditCycleTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IEditCycleTab::backTriggered, this, &CEditCycleWindow::backTriggered);
}
