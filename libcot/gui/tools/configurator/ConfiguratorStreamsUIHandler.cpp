#include "ConfiguratorStreamsUIHandler.h"

ConfiguratorStreamsUIHandler::ConfiguratorStreamsUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorStreamsUIHandler::~ConfiguratorStreamsUIHandler()
{

}

void ConfiguratorStreamsUIHandler::layout()
{
    //TODO
}

int ConfiguratorStreamsUIHandler::columnCount() const
{
    //TODO
    return 0;
}

QWidget *ConfiguratorStreamsUIHandler::createWidget(int column, IVariable *ivar)
{
    //TODO
    return Q_NULLPTR;
}

void ConfiguratorStreamsUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    //TODO
}

void ConfiguratorStreamsUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    //TODO
}

void ConfiguratorStreamsUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    //TODO
}
