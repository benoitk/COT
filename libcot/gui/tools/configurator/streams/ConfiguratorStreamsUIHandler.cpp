#include "ConfiguratorStreamsUIHandler.h"
#include "CPushButton.h"
#include "CToolButton.h"

#include <CVariableStream.h>
#include <CVariableMeasure.h>
#include <CAutomate.h>
#include <CVariableFactory.h>

#include <QWidget>
#include <QGridLayout>
#include <QDebug>

ConfiguratorStreamsUIHandler::ConfiguratorStreamsUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsUpdated, this, &ConfiguratorStreamsUIHandler::layout);
}

ConfiguratorStreamsUIHandler::~ConfiguratorStreamsUIHandler()
{
}

void ConfiguratorStreamsUIHandler::layout()
{
    QList<IVariable *> listVar;
    foreach(CVariableStream* stream, CAutomate::getInstance()->getListStreams()){
        listVar << stream;
        const QList<IVariable *> lstVar = stream->getListMeasures();
        foreach (IVariable *var, lstVar) {
            listVar << var;
        }
    }
    IConfiguratorUIHandler::layout(listVar, false);
}

int ConfiguratorStreamsUIHandler::columnCount() const
{
    return 4;
}

QWidget *ConfiguratorStreamsUIHandler::createWidget(int column, IVariable *ivar)
{

    const bool isStream = ivar && ivar->getType() == type_stream;
    switch (column) {
        case 0: {
            return isStream ? newItemButton(ivar) : Q_NULLPTR;
        }
        case 1: {
            return isStream ? Q_NULLPTR : newItemButton(ivar);
        }
        case 2: {
            return newDeleteButton(ivar);
        }
        case 3: {
            return isStream ? addMeasureButton(ivar) : Q_NULLPTR;
        }
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
    const bool isStream = ivar && ivar->getType() == type_stream;

    if (isStream) {
        row.widgetAt<CPushButton *>(0)->setText(ivar->getLabel());
    }
    else {
        row.widgetAt<CPushButton *>(1)->setText(ivar->getLabel());
    }
}

void ConfiguratorStreamsUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    CAutomate *automate = CAutomate::getInstance();

    CVariableStream *varStream = qobject_cast<CVariableStream *>(ivar);

    if (varStream && ivar->getType() == type_stream) {
        automate->delStream(varStream);

    } else if (ivar->getType() == type_measure) {
        CVariableMeasure *varMeasure = qobject_cast<CVariableMeasure *>(ivar);
        if (!varMeasure)
            return;
        varStream = getStreamForMeasure(varMeasure);
        if (varStream)
            varStream->delMeasure(varMeasure);
    }
}

CPushButton *ConfiguratorStreamsUIHandler::newItemButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    connect(button, &CPushButton::clicked, this, &ConfiguratorStreamsUIHandler::itemClicked);
    return button;
}

IVariable *ConfiguratorStreamsUIHandler::getVariable(const QString &name)
{
    CAutomate *automate = CAutomate::getInstance();
    const QList<CVariableStream*> streams = automate->getListStreams();
    foreach (CVariableStream *streamVar, streams) {
        if (streamVar->getName() == name) {
            return streamVar;
        }

        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measureIvar);
            if (measureVar->getName() == name) {
                return measureVar;
            }
        }
    }

    return IVariableUIHandler::getVariable(name);
}

CToolButton *ConfiguratorStreamsUIHandler::addMeasureButton(IVariable *ivar)
{    
    CToolButton *button = new CToolButton(CToolButton::Add);
    button->setFixedSize(21, 21);
    button->setUserData(ivar->getName());
    connect(button, &CToolButton::clicked, this, &ConfiguratorStreamsUIHandler::addItem);
    return button;
}

CVariableStream *ConfiguratorStreamsUIHandler::getStreamForMeasure(CVariableMeasure *measure)
{
    CAutomate *automate = CAutomate::getInstance();
    const QList<CVariableStream*> streams = automate->getListStreams();
    foreach (CVariableStream *streamVar, streams) {
        if (streamVar->getName() == measure->getName()) {
            continue;
        }

        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measureIvar);
            if (measureVar->getName() == measure->getName()) {
                return streamVar;
            }
        }
    }
    return Q_NULLPTR;
}

void ConfiguratorStreamsUIHandler::itemClicked()
{
    CPushButton *item = qobject_cast<CPushButton *>(sender());
    if (!item) {
        return;
    }

    IVariable *ivar = getVariable(item->userData().toString());

    if (!ivar) {
        return;
    }

    QString label = ivar->getLabel();
    enterText(label);
    ivar->setLabel(label);
}

void ConfiguratorStreamsUIHandler::addItem()
{
    CToolButton *item = qobject_cast<CToolButton *>(sender());
    if (!item) {
        return;
    }

    IVariable *ivar = getVariable(item->userData().toString());

    if (!ivar) {
        return;
    }

    QString label;
    enterText(label);

    CVariableStream *varStream = qobject_cast<CVariableStream *>(ivar);
    CVariableMeasure *varMeasure = qobject_cast<CVariableMeasure *>(CVariableFactory::buildTemporary(label, type_measure));
    if (!varMeasure)
        return;
    varStream = getStreamForMeasure(varMeasure);
    if (varStream)
        varStream->addMeasure(varMeasure);
    layout();
}
