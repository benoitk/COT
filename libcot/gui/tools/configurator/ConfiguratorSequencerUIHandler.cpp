#include "ConfiguratorSequencerUIHandler.h"

ConfiguratorSequencerUIHandler::ConfiguratorSequencerUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorSequencerUIHandler::~ConfiguratorSequencerUIHandler()
{

}

void ConfiguratorSequencerUIHandler::layout()
{
    //TODO
}

int ConfiguratorSequencerUIHandler::columnCount() const
{
    //TODO
    return 0;
}

QWidget *ConfiguratorSequencerUIHandler::createWidget(int column, IVariable *ivar)
{
    //TODO
    return Q_NULLPTR;
}

void ConfiguratorSequencerUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    //TODO
}

void ConfiguratorSequencerUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    //TODO
}

void ConfiguratorSequencerUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    //TODO
}
