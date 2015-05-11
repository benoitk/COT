#include "ConfiguratorStreamsUIHandler.h"
#include <QWidget>
#include <QGridLayout>
#include <CPushButton.h>
#include <CToolButton.h>
#include <CVariableStream.h>
#include <CAutomate.h>

ConfiguratorStreamsUIHandler::ConfiguratorStreamsUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorStreamsUIHandler::~ConfiguratorStreamsUIHandler()
{

}

void ConfiguratorStreamsUIHandler::layout()
{
    const QList<IVariable *> listVar = CAutomate::getInstance()->getMapStreams().values();
    IConfiguratorUIHandler::layout(listVar, false);
}

int ConfiguratorStreamsUIHandler::columnCount() const
{
    return 1;
}

QWidget *ConfiguratorStreamsUIHandler::createWidget(int column, IVariable *ivar)
{
    if (!ivar || (ivar->getType() != type_stream)) {
        return Q_NULLPTR;
    }
    if (column == 1) {
        QWidget *mainwidget = new QWidget;
        QGridLayout *grid = new QGridLayout(mainwidget);
        CPushButton *streamButton = newButton(ivar);
        grid->addWidget(streamButton, 0, 0);
        grid->addWidget(newDeleteButton(ivar), 0, 3);
        CVariableStream *streamVariable = static_cast<CVariableStream *>(ivar);
        const QList<IVariable *> lstVar = streamVariable->getListMeasures();
        int row = 0;
        foreach (IVariable *var, lstVar) {
            row++;
            grid->addWidget(newButton(var), row, 1);
            grid->addWidget(newDeleteButton(var), row, 2);
        }
        grid->addWidget(addMeasureButton(), row, 4);
        return mainwidget;
    }
    return Q_NULLPTR;
}

void ConfiguratorStreamsUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void ConfiguratorStreamsUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    QWidget *mainWidget = row.widgetAt<QWidget *>(0);
    if (mainWidget) {

    }
    //TODO
}

void ConfiguratorStreamsUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    //TODO
}

CPushButton *ConfiguratorStreamsUIHandler::newButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(m_container);
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    return button;
}

CPushButton *ConfiguratorStreamsUIHandler::addMeasureButton()
{
    CPushButton *button = new CPushButton(m_container);
    //TODO customize
    button->setText(tr("Add measure"));
    return button;
}
