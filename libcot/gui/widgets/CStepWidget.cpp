#include "CStepWidget.h"
#include "CEditStepListTab.h"
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
#include <QPainter>
#include <QLabel>
#include <QAction>
#include <QDebug>
#include <StyleRepository.h>

const float CStepWidget::STEP_STOP_INTERVAL = -1.0;

CStepWidget::CStepWidget(CAutomate* arg_automate, CStep *step, CEditStepListTab *parent)
    : QGroupBox(parent)
    , m_interval(new QLabel(this))
    , m_scrollable(new IScrollableUIWidget(false, this))
    , m_handler(new CStepWidgetUIHandler(arg_automate, m_scrollable->scrollableWidget(), this))
    , m_stepDescriber(new CVariableCStepDescriber(arg_automate, m_handler)) // m_handler is absolutly not related to this describer, but ctor do need one.
    , m_selected(false)
    , m_oldValue(step->getNumStep())
    , m_automate(arg_automate)
{
    Q_ASSERT(step);
    Q_ASSERT(parent);

    m_stepDescriber->describe(QVariant::fromValue(step));

    QSizePolicy policy = sizePolicy();
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    setSizePolicy(policy);

    CVerticalButtonBar *vbb = m_scrollable->buttonBar();
    connect(vbb->addAction(CToolButton::Add), &QAction::triggered, this, &CStepWidget::slotAddTriggered);
    connect(vbb->addAction(CToolButton::Edit), &QAction::triggered, this, &CStepWidget::slotEditTriggered);
    connect(vbb->addAction(CToolButton::Remove), &QAction::triggered, this, &CStepWidget::signalDeleteRequested);

    foreach (CToolButton *button, m_scrollable->buttonBar()->findChildren<CToolButton *>()) {
        button->setFixedSize(StyleRepository::configuratorButtonSize());
    }

    QHBoxLayout *hl = new QHBoxLayout(this);
    hl->addWidget(m_interval, 0, Qt::AlignLeft | Qt::AlignTop);
    hl->addWidget(m_scrollable);

    m_handler->layout(step);
    slotUpdateInfos(false);
}

bool CStepWidget::isSelected() const
{
    return m_selected;
}

void CStepWidget::setSelected(bool selected)
{
    if (isStopStep()) {
        return;
    }

    if (m_selected != selected) {
        m_selected = selected;
        update();
    }
}

void CStepWidget::setInterval(float value)
{
    m_stepDescriber->getVariable("interval")->setValue(value);
    slotUpdateInfos(false);
}

bool CStepWidget::isStopStep() const
{
    return qFuzzyCompare(getInterval() +1.0, STEP_STOP_INTERVAL +1.0);
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
    return m_stepDescriber->getVariable("interval")->toFloat();
}

QList<IAction *> CStepWidget::getActions() const
{
    QList<IAction *> actions;
    foreach (IVariable *ivar, m_handler->describer()->getVariables()) {
        IAction *action = m_automate->getAction(ivar->toString());
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

void CStepWidget::paintEvent(QPaintEvent *event)
{
    QGroupBox::paintEvent(event);

    if (m_selected) {
        // Because of stylesheet style, can't use QStyleOptionFocusRect / QStyle::PE_FrameFocusRect
        // Let draw ourselves...
        QColor highlight = palette().color(QPalette::Highlight);
        highlight.setAlpha(30);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(highlight.darker(130));
        painter.setBrush(highlight);
        painter.drawRoundedRect(rect().adjusted(2, 2, -2, -2), 5, 5);
    }
}

void CStepWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QGroupBox::mouseReleaseEvent(event);
    setSelected(!isSelected());
}

void CStepWidget::slotUpdateInfos(bool emitSignal)
{
    const float newValue = m_stepDescriber->getVariable("interval")->toFloat();
    setTitle(m_stepDescriber->getVariable("label")->toString());
    m_interval->setText(newValue < 0 ? tr("Stop") : m_stepDescriber->getVariable("interval")->toString());

    if (emitSignal) {
        if (!qFuzzyCompare(m_oldValue +1.0, newValue +1.0)) {
            emit signalStepChanged(m_oldValue, newValue);
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
    m_oldValue = getInterval();
    CGenericVariablesEditorWindow *window = new CGenericVariablesEditorWindow(m_automate, this);
    window->setValidator(CEditStepListTab::validateStepWidget, this, parentWidget());
    window->setVariables(tr("Step"), m_stepDescriber->getVariables(), true);
    connect(window, &CGenericVariablesEditorWindow::signalPropertiesApplied, this, &CStepWidget::slotUpdateInfosWithSignal);
    CPCWindow::openModal(window);
}
