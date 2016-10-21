#include "CEditStepListTab.h"
#include "CScrollablePagerWidget.h"
#include "IVariableUIHandler.h"
#include "CStepWidget.h"
#include "CGenericVariablesEditor.h"
#include "CMessageBox.h"
#include "CPCWindow.h"

#include <ICycle.h>
#include <CStep.h>

#include <QVBoxLayout>
#include <QTimer>
#include <QScrollBar>
#include <QDebug>

bool lessThanStepWidget(CStepWidget *left, CStepWidget *right) {
    return left->getInterval() < right->getInterval();
}

int findTargetIndex(QBoxLayout *layout, float interval) {
    int index = -1;
    for (int i = 0; i < layout->count(); ++i) {
        CStepWidget *stepWidget = qobject_cast<CStepWidget *>(layout->itemAt(i)->widget());
        if (!layout->itemAt(i)->widget()) { continue; } else { Q_ASSERT(stepWidget); }

        const float stepInterval = stepWidget->getInterval();

        index = i;

        if (stepInterval > interval) {
            break;
        }
    }

    CStepWidget *sw = qobject_cast<CStepWidget *>(layout->itemAt(index)->widget());
    if (!sw || sw->getInterval() < interval) {
        index = -1;
    }

    return index;
}

CEditStepListTab::CEditStepListTab(CAutomate* arg_automate, ICycle *cycle, QWidget *parent)
    : IConfiguratorEditTab(parent)
    , m_widget(new CScrollablePagerWidget(this))
    , m_layout(new QVBoxLayout(m_widget))
    , m_automate(arg_automate)
{
    m_layout->addStretch();
    m_cycle = cycle;
    QList<CStep *> steps = cycle->getListSteps();

    if (cycle->getStepStop()) {
        steps.prepend(cycle->getStepStop());
    }

    foreach (CStep *step, steps) {
        addStep(step);
    }

    scrollableWidget()->setScrollablePagerWidget(m_widget);

    scrollableWidget()->moveUp()->disconnect();
    scrollableWidget()->moveDown()->disconnect();

    connect(scrollableWidget()->moveUp(), &QAction::triggered, this, &CEditStepListTab::slotMoveUp);
    connect(scrollableWidget()->moveDown(), &QAction::triggered, this, &CEditStepListTab::slotMoveDown);
    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CEditStepListTab::slotAddStep);
    connect(buttonBar()->addAction(CToolButton::AddStopStep), &QAction::triggered, this, &CEditStepListTab::slotAddStopStep);
    connect(buttonBar()->addAction(CToolButton::Copy), &QAction::triggered, this, &CEditStepListTab::slotCopyTriggered);
    connect(buttonBar()->addAction(CToolButton::Move), &QAction::triggered, this, &CEditStepListTab::slotMoveTriggered);
    initBaseTab();
}

void CEditStepListTab::applyProperties(const QVariant &object)
{
    ICycle *cycle = object.value<ICycle *>();
    Q_ASSERT(cycle);
    CStep *stopStep = Q_NULLPTR;
    QList<CStep *> steps;

    foreach (CStepWidget *stepWidget, findChildren<CStepWidget*>()) {
        if (stepWidget->isStopStep()) {
            Q_ASSERT(!stopStep);
            stopStep = stepWidget->createNewStep();
        }
        else {
            steps << stepWidget->createNewStep();
        }
    }

    cycle->setListSteps(steps, stopStep);
}

void CEditStepListTab::ensureStepWidgetVisible(CStepWidget *stepWidget)
{
    // We have to delay the call when creating new widget so the layout mechanism have time to relayout the widget.
    QTimer::singleShot(100, [this, stepWidget]() { scrollableWidget()->ensureWidgetVisible(stepWidget, 0, 0); });
}

CStepWidget *CEditStepListTab::addStep(CStep *step)
{
    CStepWidget *sw = new CStepWidget(m_automate, step, this);
    connect(sw, &CStepWidget::signalStepChanged, this, &CEditStepListTab::slotHandleStepChanged);
    connect(sw, &CStepWidget::signalDeleteRequested, this, &CEditStepListTab::slotHandleDeleteRequest);
    m_layout->insertWidget(m_layout->count() -1, sw); // -1 to add before last item which is stretch
    return sw;
}

CStepWidget *CEditStepListTab::stepWidgetAt(int index) const
{
    return index >= 0 && index < m_layout->count()
            ? qobject_cast<CStepWidget *>(m_layout->itemAt(index)->widget()) : Q_NULLPTR;
}

QList<CStepWidget *> CEditStepListTab::selectedSteps() const
{
    QList<CStepWidget *> steps;

    for (int i = 0; i < m_layout->count(); ++i) {
        CStepWidget *stepWidget = stepWidgetAt(i);
        if (!m_layout->itemAt(i)->widget()) { continue; } else { Q_ASSERT(stepWidget); }

        if (stepWidget->isSelected()) {
            steps << stepWidget;

            // We need contiguous selection to operate
            if (steps.first() != stepWidget) {
                const int previousIndex = m_layout->indexOf(steps.value(steps.count() -2));
                const int index = m_layout->indexOf(steps.value(steps.count() -1));

                if (index -1 != previousIndex) {
                    CPCWindow::openModal<CMessageBox>(tr("You must provide a contiguous selection."));
                    return QList<CStepWidget *>();
                }
            }
        }
    }

    return steps;
}

void CEditStepListTab::copySteps(const QList<CStepWidget *> &stepWidgets, float to)
{
    // SERES_TODO: Implement copy algorythm.
    m_cycle->moveSteps(stepWidgets.first()->getInterval(), stepWidgets.count(), to);
    this->slotDeleteAll();
    foreach(CStep* step, m_cycle->getListSteps()){
        addStep(step);
    }

}

void CEditStepListTab::moveSteps(const QList<CStepWidget *> &stepWidgets, float to)
{
    // SERES_TODO: Implement move algorythm. (this one is bugguy and not finished)

    // Reminder about each step durations
    QMap<CStepWidget *, float> stepsDuration;
    for (int i = 0; i < m_layout->count(); ++i) {
        CStepWidget *stepWidget = stepWidgetAt(i);
        CStepWidget *nextStepWidget = stepWidgetAt(i +1);
        if (!m_layout->itemAt(i)->widget()) { continue; } else { Q_ASSERT(stepWidget); }

        // assume a step run at least for 1 second for latest step.
        stepsDuration[stepWidget] = nextStepWidget ? nextStepWidget->getInterval() -stepWidget->getInterval() : 1;
    }

    const QSet<CStepWidget *> movingStepWidgets = stepWidgets.toSet();
    CStepWidget *targetStepWidget = stepWidgetAt(findTargetIndex(m_layout, to));
    const float offset = to -stepWidgets.first()->getInterval();
    QList<QLayoutItem *> items;

    // remove items to move
    const bool movingUp = offset < 0;
    for (int i = m_layout->count() -1; i >= 0; --i) {
        CStepWidget *stepWidget = stepWidgetAt(i);
        if (!m_layout->itemAt(i)->widget()) { continue; } else { Q_ASSERT(stepWidget); }

        if (movingStepWidgets.contains(stepWidget)) {
            if (movingUp) {
                items.prepend(m_layout->takeAt(i));
            }
            else {
                items.append(m_layout->takeAt(i));
            }
        }
    }

    // reinsert them
    foreach (QLayoutItem *item, items) {
        // -1 because latest item is a stretch item
        const int index = targetStepWidget ? m_layout->indexOf(targetStepWidget) : m_layout->count() -1;
        m_layout->insertItem(index, item);
        CStepWidget *stepWidget = stepWidgetAt(index);
        Q_ASSERT(stepWidget);
        stepWidget->setInterval(stepWidget->getInterval() +offset);

        if (!targetStepWidget) {
            targetStepWidget = stepWidget;
        }
    }

    // Updating items interval
    for (int i = 0; i < m_layout->count(); ++i) {
        CStepWidget *stepWidget = stepWidgetAt(i);
        CStepWidget *previousStepWidget = stepWidgetAt(i -1);
        if (!m_layout->itemAt(i)->widget()) { continue; } else { Q_ASSERT(stepWidget); }

        if (previousStepWidget) {
            stepWidget->setInterval(previousStepWidget->getInterval() +stepsDuration.value(previousStepWidget, 0));
        }
    }
}

void CEditStepListTab::reorderStepWidgets(CStepWidget *ensureVisibleStep)
{
    QList<CStepWidget *> stepWidgets = findChildren<CStepWidget *>();
    qStableSort(stepWidgets.begin(), stepWidgets.end(), lessThanStepWidget);

    // clear layout items
    for (int i = m_layout->count() -1; i >= 0; --i) {
        delete m_layout->takeAt(i);
    }

    foreach (CStepWidget *stepWidget, stepWidgets) {
        m_layout->addWidget(stepWidget);
    }

    m_layout->addStretch();

    if (ensureVisibleStep) {
        ensureStepWidgetVisible(ensureVisibleStep);
    }
}

bool CEditStepListTab::hasExistingInterval(float interval, CStepWidget *byPass) const
{
    foreach (CStepWidget *sw, findChildren<CStepWidget *>()) {
        if (sw == byPass) {
            continue;
        }

        if (qFuzzyCompare(sw->getInterval() +1.0, interval +1.0)) {
            return true;
        }
    }

    return false;
}

void CEditStepListTab::slotMoveUp()
{
    const int step = scrollableWidget()->getPageStep();
    QScrollBar* sb = scrollableWidget()->verticalScrollBar();
    sb->setSliderPosition(sb->sliderPosition() - (step /2));
    scrollableWidget()->updateActions();
}

void CEditStepListTab::slotMoveDown()
{
    const int step = scrollableWidget()->getPageStep();
    QScrollBar* sb = scrollableWidget()->verticalScrollBar();
    sb->setSliderPosition(sb->sliderPosition() + (step /2));
    scrollableWidget()->updateActions();
}

bool CEditStepListTab::validateStepWidget(CGenericVariablesEditor *editor, void *userData1, void *userData2)
{
    const float interval = editor->getVariable("interval")->toFloat();
    CStepWidget *stepWidget = static_cast<CStepWidget *>(userData1);
    CEditStepListTab *editStepListTab = static_cast<CEditStepListTab *>(userData2);

    if (editStepListTab->hasExistingInterval(interval, stepWidget)) {
        CPCWindow::openModal<CMessageBox>(tr("You can't use interval %1, it's already used by another step.\n"
                                             "Please change your interval.").arg(interval));
        return false;
    }

    return true;
}

void CEditStepListTab::slotAddStep()
{
    const CStepWidget *sw = stepWidgetAt(m_layout->count() -2); // last item is a stretch
    CStep *step = new CStep;
    step->setNumStep(sw ? sw->getInterval() +1.0 : 0.0);
    step->setLabel(tr("New step"));
    CStepWidget *stepWidget = addStep(step);
    reorderStepWidgets(stepWidget);
    stepWidget->editStep();
}

void CEditStepListTab::slotAddStopStep()
{
    if (hasExistingInterval(CStepWidget::STEP_STOP_INTERVAL)) {
        CMessageBox *mb = new CMessageBox(tr("You already have a stop step, scrolling to it."));
        connect(mb, &QWidget::destroyed, this, &CEditStepListTab::slotScrollToStopStep);
        CPCWindow::openModal(mb);
        return;
    }

    CStep *step = new CStep;
    step->setNumStep(CStepWidget::STEP_STOP_INTERVAL);
    step->setLabel(tr("New stop step"));
    CStepWidget *stepWidget = addStep(step);
    reorderStepWidgets(stepWidget);
    stepWidget->editStep();
}

void CEditStepListTab::slotCopyTriggered()
{
    const QList<CStepWidget *> steps = selectedSteps();

    if (steps.isEmpty()) {
        return;
    }

    float to = 0.0;
    if (!IVariableUIHandler::enterFloat(to,1, tr("Enter the destination interval (copy)"))) {
        return;
    }

    if (to < 0) {
        CPCWindow::openModal<CMessageBox>(tr("You must provide a destination >= 0."));
        return;
    }

    copySteps(steps, to);
}

void CEditStepListTab::slotMoveTriggered()
{
    const QList<CStepWidget *> steps = selectedSteps();

    if (steps.isEmpty()) {
        return;
    }

    float to = 0.0;
    if (!IVariableUIHandler::enterFloat(to, 1,tr("Enter the destination interval (move)"))) {
        return;
    }

    if (to < 0) {
        CPCWindow::openModal<CMessageBox>(tr("You must provide a destination >= 0."));
        return;
    }

    moveSteps(steps, to);
}

void CEditStepListTab::slotScrollToStopStep()
{
    CStepWidget *sw = Q_NULLPTR;

    foreach (CStepWidget *stepWidget, findChildren<CStepWidget*>()) {
        if (stepWidget->isStopStep()) {
            sw = stepWidget;
            break;
        }
    }

    if (sw) {
        ensureStepWidgetVisible(sw);
    }
}

void CEditStepListTab::slotHandleStepChanged(float from, float to)
{
    Q_UNUSED(from)
    Q_UNUSED(to);

    CStepWidget *sw = qobject_cast<CStepWidget *>(sender());
    Q_ASSERT(sw);

    // Editing a step is a special move case, to handle it generically, we must set it back to its previous value
    // then call moveSteps
    /*sw->setInterval(from);
    moveSteps(QList<CStepWidget *>() << sw, to);*/
    reorderStepWidgets(sw);
}
void CEditStepListTab::slotDeleteAll(){
    for (int i = m_layout->count() -1; i >= 0; --i) {
        delete m_layout->takeAt(i);
    }
}

void CEditStepListTab::slotHandleDeleteRequest()
{
    CStepWidget *sw = qobject_cast<CStepWidget *>(sender());
    m_layout->removeWidget(sw);
    sw->deleteLater();
    // SERES_TODO: Handle algorythm behavior on step deletion
    // For now just reusing standard reordering algo
    reorderStepWidgets();
}
