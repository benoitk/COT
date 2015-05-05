#include "ConfiguratorVariablesUIHandler.h"

ConfiguratorVariablesUIHandler::ConfiguratorVariablesUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : ConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorVariablesUIHandler::~ConfiguratorVariablesUIHandler()
{

}

int ConfiguratorVariablesUIHandler::columnCount() const
{
    return ConfiguratorUIHandler::columnCount();
}

QWidget *ConfiguratorVariablesUIHandler::createWidget(int column, IVariable *ivar)
{
    return ConfiguratorUIHandler::createWidget(column, ivar);
}

void ConfiguratorVariablesUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    ConfiguratorUIHandler::rowInserted(row, ivar);
}

void ConfiguratorVariablesUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    ConfiguratorUIHandler::rowChanged(row, ivar);
}

