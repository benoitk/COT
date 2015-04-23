#include "CPCMeasureTab.h"
#include "ui_CPCMeasureTab.h"
#include "CPCWindow.h"
#include "CMeasureWindow.h"
#include "CToolButton.h"
#include "CAutomate.h"
#include "IVariable.h"
#include "CUnit.h"

#include <QGridLayout>
#include <QLabel>

namespace {
QString valueAndUnit(IVariable *ivar) {
    const CUnit *unit = ivar->getUnit();
    return QString("%1%2").arg(ivar->toString()).arg(unit ? unit->getLbl() : QString());
}

CToolButton *newButton(IVariable *ivar, QWidget *parent = Q_NULLPTR) {
    CToolButton *button = new CToolButton(CToolButton::MeasureDetails, parent);
    button->setFixedSize(30, 30);
    button->setUserData(ivar->getRelatedStreamName());
    return button;
}

QLabel *newLabel(IVariable *ivar, QWidget *parent = Q_NULLPTR) {
    QLabel *l = new QLabel(ivar->getLabel(), parent);
    l->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QPalette pal = l->palette();
    pal.setColor(l->foregroundRole(), QColor(Qt::gray));
    l->setPalette(pal);
    return l;
}

QLabel *newValueUnit(IVariable *ivar, QWidget *parent = Q_NULLPTR) {
    QLabel *l = new QLabel(valueAndUnit(ivar), parent);
    l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    return l;
}
}

CPCMeasureTab::CPCMeasureTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCMeasureTab)
    , m_container(Q_NULLPTR)
    , m_containerLayout(Q_NULLPTR)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    slotUpdateStreamsMeasures();

    connect(ui->vbbButtons->addAction(CToolButton::Alarms), &QAction::triggered,
            this, &CPCMeasureTab::slotAlarmsTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Play), &QAction::triggered,
            this, &CPCMeasureTab::slotPlayTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::Stop), &QAction::triggered,
            this, &CPCMeasureTab::slotStopTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::StopEndCycle), &QAction::triggered,
            this, &CPCMeasureTab::slotStopEndCycleTriggered);
    connect(ui->vbbButtons->addAction(CToolButton::NextStream), &QAction::triggered,
            this, &CPCMeasureTab::slotNextStreamTriggered);
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsMeasuresChanged,
            this, &CPCMeasureTab::slotUpdateStreamsMeasures);
    connect(CAutomate::getInstance(), &CAutomate::signalStreamMeasureChanged,
            this, &CPCMeasureTab::slotStreamMeasureChanged);
}

CPCMeasureTab::~CPCMeasureTab()
{
    delete ui;
}

void CPCMeasureTab::slotAlarmsTriggered()
{

}

void CPCMeasureTab::slotPlayTriggered()
{

}

void CPCMeasureTab::slotStopTriggered()
{

}

void CPCMeasureTab::slotStopEndCycleTriggered()
{

}

void CPCMeasureTab::slotNextStreamTriggered()
{

}

void CPCMeasureTab::slotButtonMeasureDetailsClicked()
{
    const CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString stream = button->userData().toString();
    CPCWindow::openModal<CMeasureWindow>(stream);
}

void CPCMeasureTab::slotUpdateStreamsMeasures()
{
    // Clean old widgets
    delete m_containerLayout;
    delete m_container;
    m_rows.clear();

    // Create new rows
    m_container = new QWidget(this);
    m_containerLayout = new QGridLayout(m_container);
    m_containerLayout->setMargin(0);

    CAutomate *automate = CAutomate::getInstance();
    const QMap<QString, QList<QString>> streams = automate->getMapStreamsMeasures();
    int y = 0;

    foreach ( const QString &stream, streams.keys()) {
        const QList<QString> streamVariables = streams[stream];

        foreach (const QString &variable, streamVariables) {
            IVariable *ivar = automate->getVariable(variable);
            Q_ASSERT(ivar);

            // KDAB: Variable must be a measure variable
            if (!ivar->isMeasureRelated()) {
                continue;
            }

            Row row;
            row.button = newButton(ivar, m_container);
            row.label = newLabel(ivar, m_container);
            row.valueUnit = newValueUnit(ivar, m_container);
            m_rows[variable] = row;

            connect(row.button, &CToolButton::clicked, this, &CPCMeasureTab::slotButtonMeasureDetailsClicked);

            m_containerLayout->addWidget(row.button, y, 0);
            m_containerLayout->addWidget(row.label, y, 1);
            m_containerLayout->addWidget(row.valueUnit, y, 2);
            y++;
        }
    }

    ui->swCentral->setScrollableWidget(m_container);
}

void CPCMeasureTab::slotStreamMeasureChanged(const QString &name)
{
    const Row row = m_rows.value(name);
    IVariable *ivar = CAutomate::getInstance()->getVariable(name);
    Q_ASSERT(row.button);
    Q_ASSERT(ivar);
    row.label->setText(ivar->getLabel());
    row.valueUnit->setText(valueAndUnit(ivar));
}
