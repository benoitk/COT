#include "CStepWidgetUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CToolButton.h"
#include "CPushButton.h"

#include <CStep.h>
#include <IAction.h>
#include <CAutomate.h>

#include <QDebug>

CStepWidgetUIHandler::CStepWidgetUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableCStepActionsDescriber(this));
}

void CStepWidgetUIHandler::layout(CStep *step)
{
    describer()->describe(QVariant::fromValue(step));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}

void CStepWidgetUIHandler::layout(const QStringList &actions)
{
    describer()->describe(actions);
    IConfiguratorUIHandler::layout(describer()->getVariables());
}

int CStepWidgetUIHandler::columnCount() const
{
    return 2;
}

QWidget *CStepWidgetUIHandler::createWidget(int column, IVariable *ivar)
{
    switch (column) {
        case 0:
            return newEditor(ivar);

        case 1:
            return newDeleteButton(ivar);
    }

    return Q_NULLPTR;
}

void CStepWidgetUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void CStepWidgetUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    CAutomate *automate = CAutomate::getInstance();
    const QString actionName = ivar->toString();
    IAction *action = automate->getAction(actionName);

    Q_ASSERT(action);

    // present label
    QString text = action->getLabel();
    // or present name if label is empty
    if (text.isEmpty()) {
        text = action->getName();
    }

    const bool locked = ivar->blockSignals(true);
    ivar->setLabel(action->getLabel());
    ivar->blockSignals(locked);
    row.widgetAt<CPushButton *>(0)->setText(text);
}

void CStepWidgetUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    CVariableCStepActionsDescriber *describer = castedDescriber<CVariableCStepActionsDescriber *>();
    QStringList names = describer->getActionList();
    const QString name = ivar->toString();
    names.removeOne(name);
    describer->describe(names);
}

void CStepWidgetUIHandler::rowDeleted(const QString &name)
{
    Q_UNUSED(name);
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
