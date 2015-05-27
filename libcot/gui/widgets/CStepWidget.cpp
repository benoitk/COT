#include "CStepWidget.h"
#include "IScrollableUIWidget.h"
#include "CStepWidgetUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"
#include "CGenericVariablesEditorWindow.h"
#include "CPCWindow.h"

#include <CAutomate.h>
#include <CStep.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QAction>
#include <QDebug>

CStepWidget::CStepWidget(CStep *step, QWidget *parent)
    : QGroupBox(parent)
    , m_interval(new QLabel(this))
    , m_scrollable(new IScrollableUIWidget(false, this))
    , m_handler(new CStepWidgetUIHandler(m_scrollable->scrollableWidget(), this))
    , m_stepDescriber(new CVariableCStepDescriber(m_handler)) // m_handler is absolutly not related to this describer, but ctor do need one.
{
    Q_ASSERT(step);

    m_stepDescriber->describe(QVariant::fromValue(step));
    m_scrollable->scrollableWidget()->setWidgetResizable(true);

    QSizePolicy policy = sizePolicy();
    policy.setVerticalPolicy(QSizePolicy::Maximum);
    setSizePolicy(policy);

    CVerticalButtonBar *vbb = m_scrollable->buttonBar();
    connect(vbb->addAction(CToolButton::Add), &QAction::triggered, this, &CStepWidget::slotAddTriggered);
    connect(vbb->addAction(CToolButton::Edit), &QAction::triggered, this, &CStepWidget::slotEditTriggered);

    foreach (CToolButton *button, m_scrollable->buttonBar()->findChildren<CToolButton *>()) {
        button->setFixedSize(22, 22);
    }

    QHBoxLayout *hl = new QHBoxLayout(this);
    hl->addWidget(m_interval, 0, Qt::AlignLeft | Qt::AlignTop);
    hl->addWidget(m_scrollable);

    m_handler->layout(step);
    slotUpdateInfos(false);
}

bool CStepWidget::isStopStep() const
{
    return getInterval() < 0;
}

void CStepWidget::editStep()
{
    slotEditTriggered();
}

QString CStepWidget::getLabel() const
{
    return title();
}

float CStepWidget::getInterval() const
{
    return m_interval->text().toFloat();
}

QList<IAction *> CStepWidget::getActions() const
{
    CAutomate *automate = CAutomate::getInstance();
    QList<IAction *> actions;

    foreach (IVariable *ivar, m_handler->describer()->getVariables()) {
        IAction *action = automate->getAction(ivar->toString());
        Q_ASSERT(action);
        actions << action;
    }

    return actions;
}

CStep *CStepWidget::createNewStep() const
{
    CStep *step = new CStep;
    step->setLabel(getLabel());
    step->setNumStep(getInterval());
    step->setListActions(getActions());
    return step;
}

void CStepWidget::slotUpdateInfos(bool emitSignal)
{
    const float oldValue = m_interval->text().toFloat();
    const float newValue = m_stepDescriber->getVariable("interval")->toFloat();
    setTitle(m_stepDescriber->getVariable("label")->toString());
    m_interval->setText(m_stepDescriber->getVariable("interval")->toString());

    if (emitSignal) {
        if (!qFuzzyCompare(oldValue +1.0, newValue +1.0)) {
            emit signalStepChanged();
        }
    }
}

void CStepWidget::slotUpdateInfosWithSignal()
{
    slotUpdateInfos(true);
}

void CStepWidget::slotAddTriggered()
{
    CVariableCStepActionsDescriber *describer = m_handler->castedDescriber<CVariableCStepActionsDescriber *>();
    QStringList names = describer->getActionList();
    QString actionName;

    if (!m_handler->selectAction(actionName) || actionName.isEmpty() || names.contains(actionName)) {
        return;
    }

    names << actionName;
    m_handler->layout(names);
}

void CStepWidget::slotEditTriggered()
{
    CGenericVariablesEditorWindow *window = new CGenericVariablesEditorWindow(this);
    window->setVariables(tr("Step"), m_stepDescriber->getVariables(), true);
    connect(window, &CGenericVariablesEditorWindow::signalPropertiesApplied, this, &CStepWidget::slotUpdateInfosWithSignal);
    CPCWindow::openModal(window);
}
