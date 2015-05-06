#include "ConfiguratorVariablesUIHandler.h"

#include <CPushButton.h>
#include <CToolButton.h>
#include <CAutomate.h>
#include <QLabel>

ConfiguratorVariablesUIHandler::ConfiguratorVariablesUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorVariablesUIHandler::~ConfiguratorVariablesUIHandler()
{

}

void ConfiguratorVariablesUIHandler::layout()
{

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
            return newDeleteButton(ivar);
        } else if (isMeasure) {
            return newLabel(ivar);
        }
        break;
    case 3:
        if (isMeasure) {
            return newDeleteButton(ivar);
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
        connect(row.widgetAt<CPushButton *>(1), &CPushButton::clicked, this, &ConfiguratorVariablesUIHandler::slotEditClicked);
        connect(row.widgetAt<CToolButton *>(2), &CToolButton::clicked, this, &ConfiguratorVariablesUIHandler::slotDeleteClicked);
    } else if (isMeasure) {
        row.widgetAt<CPushButton *>(1)->setText(ivar->getLabel());
        connect(row.widgetAt<CPushButton *>(1), &CPushButton::clicked, this, &ConfiguratorVariablesUIHandler::slotEditClicked);
        connect(row.widgetAt<CToolButton *>(2), &CToolButton::clicked, this, &ConfiguratorVariablesUIHandler::slotDeleteClicked);
    }
}

void ConfiguratorVariablesUIHandler::rowAboutToBeDeleted(const Row &row, IVariable *ivar)
{
    //TODO
}

CPushButton *ConfiguratorVariablesUIHandler::newButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(m_container);
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    return button;
}

void ConfiguratorVariablesUIHandler::slotEditClicked()
{
    QString variableName = qobject_cast<CPushButton *>(sender())->userData().toString();
    emit editVariable(variableName);
}

void ConfiguratorVariablesUIHandler::slotDeleteClicked()
{
    //TODO
}
