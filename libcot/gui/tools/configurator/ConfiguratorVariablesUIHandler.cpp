#include "ConfiguratorVariablesUIHandler.h"

#include <CPushButton.h>
#include <CToolButton.h>
#include <CAutomate.h>
#include <QLabel>
#include <QDebug>

ConfiguratorVariablesUIHandler::ConfiguratorVariablesUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorVariablesUIHandler::~ConfiguratorVariablesUIHandler()
{

}

void ConfiguratorVariablesUIHandler::layout()
{
    const QList<IVariable*> listVar = CAutomate::getInstance()->getMapVariables().values();
    IVariableUIHandler::layout(listVar, false);
}

int ConfiguratorVariablesUIHandler::columnCount() const
{
    return 4;
}

QWidget *ConfiguratorVariablesUIHandler::createWidget(int column, IVariable *ivar)
{
    const bool isStream = ivar && (ivar->getType() == type_stream);
    const bool isMeasure = ivar && (ivar->getType() == type_measure);
    if(!isStream && !isMeasure) {
        return Q_NULLPTR;
    }

    switch(column) {
    case 0:
        if (isStream) {
            return newLabel(ivar);
        }
        break;
    case 1:
        if (isStream) {
            return newButton(ivar);
        } else if (isMeasure) {
            return newLabel(ivar);
        }
        break;
    case 2:
        if (isStream) {
            CToolButton *deleteButton = newDeleteButton(ivar);
            return deleteButton;
        } else if (isMeasure) {
            return newButton(ivar);
        }
        break;
    case 3:
        if (isMeasure) {
            CToolButton *deleteButton = newDeleteButton(ivar);
            return deleteButton;
        }
        break;
    }
    return Q_NULLPTR;
}

void ConfiguratorVariablesUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void ConfiguratorVariablesUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    const bool isStream = ivar && ivar->getType() == type_stream;
    const bool isMeasure = ivar && (ivar->getType() == type_measure);
    if (isStream) {
        row.widgetAt<QLabel *>(0)->setText(ivar->getLabel());
        row.widgetAt<CPushButton *>(1)->setText(ivar->getLabel());
    } else if (isMeasure) {
        row.widgetAt<QLabel *>(1)->setText(ivar->getLabel());
        row.widgetAt<CPushButton *>(2)->setText(ivar->getLabel());
    }
}

void ConfiguratorVariablesUIHandler::rowAboutToBeDeleted(const Row &row, IVariable *ivar)
{
    //TODO
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

CPushButton *ConfiguratorVariablesUIHandler::newButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    connect(button, &CPushButton::clicked, this, &ConfiguratorVariablesUIHandler::slotEditClicked);
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    return button;
}

void ConfiguratorVariablesUIHandler::slotEditClicked()
{
    QString variableName = qobject_cast<CPushButton *>(sender())->userData().toString();
    emit editVariable(variableName);
}

void ConfiguratorVariablesUIHandler::deleteVariable(const QString &name)
{
    //TODO
}
