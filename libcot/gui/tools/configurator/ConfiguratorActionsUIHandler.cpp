#include "ConfiguratorActionsUIHandler.h"

ConfiguratorActionsUIHandler::ConfiguratorActionsUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorActionsUIHandler::~ConfiguratorActionsUIHandler()
{

}

void ConfiguratorActionsUIHandler::layout()
{

}

int ConfiguratorActionsUIHandler::columnCount() const
{
    return 2;
}

QWidget *ConfiguratorActionsUIHandler::createWidget(int column, IVariable *ivar)
{
    return Q_NULLPTR;
}

void ConfiguratorActionsUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{

}

void ConfiguratorActionsUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{

}

void ConfiguratorActionsUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{

}

