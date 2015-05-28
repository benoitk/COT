#include "CEditStepListTab.h"
#include "IVariableUIHandler.h"
#include "CStepWidget.h"
#include "CMessageBox.h"
#include "CPCWindow.h"

#include <ICycle.h>
#include <CStep.h>

#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

bool lessThanStepWidget(CStepWidget *left, CStepWidget *right) {
    return left->getInterval() < right->getInterval();
}

CEditStepListTab::CEditStepListTab(ICycle *cycle, QWidget *parent)
    : IConfiguratorEditTab(parent)
    , m_widget(new QWidget(this))
    , m_layout(new QVBoxLayout(m_widget))
{
    m_layout->addStretch();

    QList<CStep *> steps = cycle->getListSteps();

    if (cycle->getStepStop()) {
        steps.prepend(cycle->getStepStop());
    }

    foreach (CStep *step, steps) {
        addStep(step);
    }

    scrollableWidget()->setScrollableWidget(m_widget);
    scrollableWidget()->setWidgetResizable(true);

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
    CStepWidget *sw = new CStepWidget(step, this);
    connect(sw, &CStepWidget::signalStepChanged, this, &CEditStepListTab::slotHandleStepChanged);
    m_layout->insertWidget(m_layout->count() -1, sw);
    return sw;
}

CStepWidget *CEditStepListTab::stepWidgetAt(int index) const
{
    return qobject_cast<CStepWidget *>(m_layout->itemAt(index)->widget());
}

QList<CStepWidget *> CEditStepListTab::selectedSteps() const
{
    QList<CStepWidget *> steps;

    for (int i = 0; i < m_layout->count() -1; ++i) { // -1 because last is a stretch item
        CStepWidget *stepWidget = qobject_cast<CStepWidget *>(m_layout->itemAt(i)->widget());
        Q_ASSERT(stepWidget);

        if (stepWidget->isSelected()) {
            steps << stepWidget;

            // We need contiguous selection to operate
            if (steps.first() != stepWidget) {
                const int previousIndex = m_layout->indexOf(steps.at(steps.count() -2));
                const int index = m_layout->indexOf(steps.at(steps.count() -1));

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

}

void CEditStepListTab::moveSteps(const QList<CStepWidget *> &stepWidgets, float to)
{
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

void CEditStepListTab::slotAddStep()
{
    CStep *step = new CStep;
    step->setNumStep(0);
    step->setLabel(tr("New step"));
    CStepWidget *stepWidget = addStep(step);
    reorderStepWidgets(stepWidget);
    stepWidget->editStep();
}

void CEditStepListTab::slotAddStopStep()
{
    foreach (CStepWidget *stepWidget, findChildren<CStepWidget*>()) {
        if (stepWidget->isStopStep()) {
            CMessageBox *mb = new CMessageBox(tr("You already have a stop step, scrolling to it."));
            connect(mb, &QWidget::destroyed, this, &CEditStepListTab::slotScrollToStopStep);
            CPCWindow::openModal(mb);
            return;
        }
    }

    CStep *step = new CStep;
    step->setNumStep(-1);
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

    double to = 0.0;
    if (!IVariableUIHandler::enterDouble(to, tr("Enter the destination interval (copy)"))) {
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

    double to = 0.0;
    if (!IVariableUIHandler::enterDouble(to, tr("Enter the destination interval (move)"))) {
        return;
    }

    if (to < 0) {
        CPCWindow::openModal<CMessageBox>(tr("You must provide a destination >= 0."));
        return;
    }

    copySteps(steps, to);
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
