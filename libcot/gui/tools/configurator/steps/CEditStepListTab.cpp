#include "CEditStepListTab.h"
#include "CStepWidget.h"
#include "CMessageBox.h"
#include "CPCWindow.h"

#include <ICycle.h>
#include <CStep.h>

#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

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
        addStep(step, false);
    }

    scrollableWidget()->setScrollableWidget(m_widget);
    scrollableWidget()->setWidgetResizable(true);

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CEditStepListTab::slotAddStep);
    connect(buttonBar()->addAction(CToolButton::AddStopStep), &QAction::triggered, this, &CEditStepListTab::slotAddStopStep);
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
    scrollableWidget()->ensureWidgetVisible(stepWidget, 0, 0);
}

CStepWidget *CEditStepListTab::addStep(CStep *step, bool ensureVisible)
{
    CStepWidget *sw = new CStepWidget(step, this);
    m_layout->insertWidget(m_layout->count() -1, sw);

    if (ensureVisible) {
        // We have to delay the call when creating new widget so the layout mechanism have time to relayout the widget.
        QTimer::singleShot(100, [this, sw]() { ensureStepWidgetVisible(sw); });
    }

    return sw;
}

void CEditStepListTab::slotAddStep()
{
    CStep *step = new CStep;
    step->setNumStep(0);
    step->setLabel(tr("New step"));
    addStep(step, true)->editStep();
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
    addStep(step, true)->editStep();
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
