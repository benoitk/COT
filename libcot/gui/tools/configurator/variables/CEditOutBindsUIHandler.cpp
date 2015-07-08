#include "CEditOutBindsUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CPushButton.h"
#include "CToolButton.h"
#include "CClickableLabel.h"

#include <CAutomate.h>

CEditOutBindsUIHandler::CEditOutBindsUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableIVariableOutBindsDescriber(this));
}

CEditOutBindsUIHandler::~CEditOutBindsUIHandler()
{
}

void CEditOutBindsUIHandler::layout(IVariable *ivar)
{
    describer()->describe(QVariant::fromValue(ivar));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}

void CEditOutBindsUIHandler::layout(const QStringList &variableNames)
{
    describer()->describe(variableNames);
    IConfiguratorUIHandler::layout(describer()->getVariables());
}

QStringList CEditOutBindsUIHandler::getBindingNames() const
{
    QStringList names;

    foreach (IVariable *ivar, describer()->getVariables()) {
        names << ivar->toString();
    }

    return names;
}

int CEditOutBindsUIHandler::columnCount() const
{
    return 3;
}

QWidget *CEditOutBindsUIHandler::createWidget(int column, IVariable *ivar)
{
    switch(column) {
        case 0:
            return newLabel(ivar);

        case 1:
            return newEditor(ivar);

        case 2:
            return newDeleteButton(ivar);
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void CEditOutBindsUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void CEditOutBindsUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    CAutomate *automate = CAutomate::getInstance();
    applyEditorConstraints(row.widgetAt<CPushButton *>(1), ivar);
    row.widgetAt<CClickableLabel *>(0)->setText(tr("Target"));
    row.widgetAt<CPushButton *>(1)->setText(automate->getVariable(ivar->toString())->getLabel());
}

void CEditOutBindsUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);

    QStringList names = getBindingNames();
    names.removeOne(ivar->toString());
    describer()->describe(names);
}

void CEditOutBindsUIHandler::rowDeleted(const QString &name)
{
    Q_UNUSED(name);
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
