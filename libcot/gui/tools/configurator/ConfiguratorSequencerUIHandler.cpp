#include "ConfiguratorSequencerUIHandler.h"

#include <QLabel>
#include <CToolButton.h>

ConfiguratorSequencerUIHandler::ConfiguratorSequencerUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorSequencerUIHandler::~ConfiguratorSequencerUIHandler()
{

}

void ConfiguratorSequencerUIHandler::layout()
{
    //TODO call layout(QList<IVariable*>)
}

int ConfiguratorSequencerUIHandler::columnCount() const
{
    return 4;
}

QWidget *ConfiguratorSequencerUIHandler::createWidget(int column, IVariable *ivar)
{
    if (!ivar) {
        return Q_NULLPTR;
    }
    switch (column) {
    case 0:
        //TODO
        break;
    case 1: {
        QLabel *lab = new QLabel(m_container);
        lab->setText(QStringLiteral("X"));
        return lab;
    }
    case 2:
        //TODO
        break;
    case 3:
        return newDeleteButton(ivar);
    }
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
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}
