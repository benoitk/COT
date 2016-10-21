#include "CEditActionTabUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CPushButton.h"
#include "CClickableLabel.h"

#include <CAutomate.h>
#include <IAction.h>

#include <QGridLayout>
#include <QDebug>

CEditActionTabUIHandler::CEditActionTabUIHandler(CAutomate* arg_automate,CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(arg_automate, scrollable, parent)
{
    setDescriber(new CVariableIActionDescriber(arg_automate,this));
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
    return IConfiguratorUIHandler::columnCount() +1;
}

QWidget *CEditActionTabUIHandler::createWidget(int column, IVariable *ivar)
{
    const QString name = ivar->getName();
    const bool isProperty = name.startsWith("property_");

    switch (column) {
        case 0: {
            CClickableLabel *label = qobject_cast<CClickableLabel *>(IConfiguratorUIHandler::createWidget(column, ivar));
            Q_ASSERT(label);

            if (isProperty) {
                QFont font = label->font();
                font.setUnderline(true);

                QPalette pal = label->palette();
                pal.setColor(label->foregroundRole(), QColor(Qt::blue));

                label->setFont(font);
                label->setPalette(pal);
                label->setCursor(Qt::PointingHandCursor);
                connect(label, &CClickableLabel::clicked, this, &CEditActionTabUIHandler::slotRequestVariable);
            }

            return label;
        }

        case 1: {
            return IConfiguratorUIHandler::createWidget(column, ivar);
        }

        case 2: {
            return IConfiguratorUIHandler::createWidget(column, ivar);
        }

        case 3: {
            return isProperty ? IConfiguratorUIHandler::newLabel(ivar) : Q_NULLPTR;
        }
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void CEditActionTabUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    IConfiguratorUIHandler::rowChanged(row, ivar);

    // Make the selected varible name in parenthesis
    CClickableLabel *label = row.widgetAt<CClickableLabel *>(3);
    if (label) {
        const QString variableName = ivar->getLabel();
        IVariable *selectedVariable = getVariable(variableName);
        label->setText(QString("(%1)").arg(selectedVariable ? selectedVariable->getLabel() : tr("Undefined")));
    }
}

QString CEditActionTabUIHandler::getVariableLabel(IVariable *ivar) const
{
    if (!ivar) {
        return IConfiguratorUIHandler::getVariableLabel(ivar);
    }

    const QString name = ivar->getName();
    const bool isProperty = name.startsWith("property_");
    const bool isConstant = name.startsWith("constant_");

    if (isProperty || isConstant) {
        const QString displayText = name.section("_", 1); // the name contains type + display text
        return displayText;
    }

    return IConfiguratorUIHandler::getVariableLabel(ivar);
}

void CEditActionTabUIHandler::slotRequestVariable()
{
    CClickableLabel *label = qobject_cast<CClickableLabel *>(sender());
    const QString name = label->userData().toString();
    IVariable *ivar = getVariable(name);
    Q_ASSERT(ivar);
    const QString oldVariableName = ivar->getLabel();
    QString newVariableName = oldVariableName;

    if (selectVariable(newVariableName, QString())) {
        if (oldVariableName == newVariableName) {
            return;
        }

        // Build new variable, see CVariableIActionDescriber::describe for logic here.
        IVariable *selectedVariable = getVariable(newVariableName);
        IVariable *property = CVariableFactory::castedBuild<IVariable *>(ivar->getAutomate(), this, selectedVariable->getType(), e_type_organ_none, selectedVariable->toVariant());
        setVariableAccess(property, e_access_read_write);
        property->setName(name);
        property->setLabel(newVariableName);

        // Update describer variable
        describer()->changeVariable(name, property);

        // Dynamically update the editors, this was not something built for that at first so, let tweak ourselves the layout.
        Row *row = getRow(name);
        Q_ASSERT(row);
        const int columnLayout = 1;
        const int rowLayout = layoutRow(*row);
        QWidget *oldEditor = row->widgets.value(columnLayout);
        QWidget *editor = createWidget(columnLayout, property);

        if (oldEditor) {
            containerLayout()->removeWidget(oldEditor);
            delete oldEditor;
            row->widgets[columnLayout] = Q_NULLPTR;
        }

        if (editor) {
            containerLayout()->addWidget(editor, rowLayout, columnLayout);
            row->widgets[columnLayout] = editor;
        }

        rowInserted(*row, property);
        rowChanged(*row, property);
    }
}
