#include "CEditInBindsUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CPushButton.h"
#include "CToolButton.h"
#include "CClickableLabel.h"

#include <CAutomate.h>

CEditInBindsUIHandler::CEditInBindsUIHandler(CAutomate* arg_automate,CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(arg_automate, scrollable, parent)
    , m_automate(arg_automate)
{
    setDescriber(new CVariableIVariableInBindsDescriber(arg_automate,this));
}

CEditInBindsUIHandler::~CEditInBindsUIHandler()
{
}

void CEditInBindsUIHandler::layout(IVariable *ivar)
{
    describer()->describe(QVariant::fromValue(ivar));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}

int CEditInBindsUIHandler::columnCount() const
{
    return 2;
}

QWidget *CEditInBindsUIHandler::createWidget(int column, IVariable *ivar)
{
    switch(column) {
        case 0:
            return newLabel(ivar);

        case 1:
            return newEditor(ivar);
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void CEditInBindsUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void CEditInBindsUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{

    applyEditorConstraints(row.widgetAt<CPushButton *>(1), ivar);
    row.widgetAt<CClickableLabel *>(0)->setText(tr("Source"));
    row.widgetAt<CPushButton *>(1)->setText(m_automate->getVariable(ivar->toString())->getLabel());
}
