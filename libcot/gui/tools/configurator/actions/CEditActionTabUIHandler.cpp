#include "CEditActionTabUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CPushButton.h"
#include "CClickableLabel.h"

#include <CAutomate.h>
#include <IAction.h>

#include <QDebug>

CEditActionTabUIHandler::CEditActionTabUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableIActionDescriber(this));
}

CEditActionTabUIHandler::~CEditActionTabUIHandler()
{
}

void CEditActionTabUIHandler::layout(IAction *action)
{
    describer()->describe(QVariant::fromValue(action));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}

int CEditActionTabUIHandler::columnCount() const
{
    return IConfiguratorUIHandler::columnCount();
}

QWidget *CEditActionTabUIHandler::createWidget(int column, IVariable *ivar)
{
    const QString name = ivar->getName();
    const bool isProperty = name.startsWith("property_");
    const bool isConstant = name.startsWith("constant_");

    switch (column) {
        case 0: {
            CClickableLabel *label = qobject_cast<CClickableLabel *>(IConfiguratorUIHandler::createWidget(column, ivar));
            Q_ASSERT(label);

            if (isProperty) {
                connect(label, &CClickableLabel::clicked, this, &CEditActionTabUIHandler::slotRequestVariable);
            }

            return label;
        }

        case 1: {
            if (isProperty || isConstant) {
                const QString mappedVariableName = ivar->getLabel(); // the current variable is in the label
                const QVariant mappedVariableValue = ivar->toVariant(); // the current value is in value
                const IVariable *mappedVariable = getVariable(mappedVariableName);

                // Build a temporary ivar to create the widget of the wanted type
                const QString displayText = name.section("_", 1); // the name contains type + display text
                IVariable *tmpVar = CVariableFactory::buildTemporary(name, displayText, mappedVariableValue, mappedVariable ? mappedVariable->getType() : type_unknow);
                QWidget *editor = IConfiguratorUIHandler::createWidget(column, tmpVar);
                delete tmpVar;
                return editor;
            }

            return IConfiguratorUIHandler::createWidget(column, ivar);
        }

        case 2: {
            return IConfiguratorUIHandler::createWidget(column, ivar);
        }
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void CEditActionTabUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    IConfiguratorUIHandler::rowInserted(row, ivar);
}

void CEditActionTabUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    const QString name = ivar->getName();
    const bool isProperty = name.startsWith("property_");
    const bool isConstant = name.startsWith("constant_");

    if (isProperty || isConstant) {
        const QString mappedVariableName = ivar->getLabel(); // the current variable is in the label
        const QVariant mappedVariableValue = ivar->toVariant(); // the current value is in value
        const IVariable *mappedVariable = getVariable(mappedVariableName);

        // Build a temporary ivar to create the widget of the wanted type
        const QString displayText = name.section("_", 1); // the name contains type + display text
        IVariable *tmpVar = CVariableFactory::buildTemporary(name, displayText, mappedVariableValue, mappedVariable ? mappedVariable->getType() : type_unknow);
        IConfiguratorUIHandler::rowChanged(row, tmpVar);
        delete tmpVar;
    }
    else {
        IConfiguratorUIHandler::rowChanged(row, ivar);
    }
}

void CEditActionTabUIHandler::slotRequestVariable()
{
    CClickableLabel *label = qobject_cast<CClickableLabel *>(sender());
    const QString name = label->userData().toString();
    IVariable *ivar = getVariable(name);
    Q_ASSERT(ivar);
    QString newName = ivar->getLabel();

    if (selectVariable(newName, QString())) {
        //ivar->setLabel(newName);
    }

    qDebug() << name;
}
