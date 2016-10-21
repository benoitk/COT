#include "ConfiguratorStreamsUIHandler.h"
#include "CScrollablePagerWidget.h"
#include "CPushButton.h"
#include "CToolButton.h"

#include <CVariableStream.h>
#include <CVariableMeasure.h>
#include <CAutomate.h>
#include <CVariableFactory.h>
#include <IConfiguratorUIHandler.h>

#include <QWidget>
#include <QGridLayout>
#include <QDebug>
#include <StyleRepository.h>

ConfiguratorStreamsUIHandler::ConfiguratorStreamsUIHandler(CAutomate* arg_automate, CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(arg_automate, scrollable, parent)
    , m_automate(arg_automate)
{
}

ConfiguratorStreamsUIHandler::~ConfiguratorStreamsUIHandler()
{
}

void ConfiguratorStreamsUIHandler::layout()
{
    QList<IVariable *> listVar;
    foreach(CVariableStream* stream, m_automate->getListStreams()){
        listVar << stream;
        listVar << stream->getListMeasures();
    }
    IConfiguratorUIHandler::layout(listVar, false);
}

int ConfiguratorStreamsUIHandler::columnCount() const
{
    return 4;
}

QWidget *ConfiguratorStreamsUIHandler::createWidget(int column, IVariable *ivar)
{
    const bool isStream = ivar && ivar->getType() == e_type_stream;

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
            return isStream ? newAddMeasureButton(ivar) : Q_NULLPTR;
        }        
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void ConfiguratorStreamsUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void ConfiguratorStreamsUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    const bool isStream = ivar && ivar->getType() == e_type_stream;
    row.widgetAt<CPushButton *>(isStream ? 0 : 1)->setText(ivar->getLabel());
}

void ConfiguratorStreamsUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    CVariableStream *varStream = qobject_cast<CVariableStream *>(ivar);

    if (ivar->getType() == e_type_stream) {
        Q_ASSERT(varStream);
        m_automate->delStream(varStream);
    } else if (ivar->getType() == e_type_measure) {
        CVariableMeasure *varMeasure = qobject_cast<CVariableMeasure *>(ivar);
        Q_ASSERT(varMeasure);

        varStream = getStreamForMeasure(varMeasure);
        Q_ASSERT(varStream);
        varStream->removeMeasure(varMeasure);
    }
}

CPushButton *ConfiguratorStreamsUIHandler::newItemButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    button->setUserData(ivar->getName());
    connect(button, &CPushButton::clicked, this, &ConfiguratorStreamsUIHandler::slotItemClicked);
    return button;
}

IVariable *ConfiguratorStreamsUIHandler::getVariable(const QString &name) const
{
    const QList<CVariableStream*> streams = m_automate->getListStreams();

    foreach (CVariableStream *streamVar, streams) {
        if (streamVar->getName() == name) {
            return streamVar;
        }

        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            if (measureIvar->getName() == name) {
                return measureIvar;
            }
        }
    }

    return IConfiguratorUIHandler::getVariable(name);
}

CToolButton *ConfiguratorStreamsUIHandler::newAddMeasureButton(IVariable *ivar)
{    
    CToolButton *button = new CToolButton(CToolButton::Add);
    button->setFixedSize(StyleRepository::configuratorButtonSize());
    button->setUserData(ivar->getName());
    connect(button, &CToolButton::clicked, this, &ConfiguratorStreamsUIHandler::slotAddItem);
    return button;
}

CVariableStream *ConfiguratorStreamsUIHandler::getStreamForMeasure(CVariableMeasure *measure)
{
    const QList<CVariableStream*> streams = m_automate->getListStreams();

    foreach (CVariableStream *streamVar, streams) {
        if (streamVar->getName() == measure->getName()) {
            Q_ASSERT(false); // this case should never happen
            continue;
        }

        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            if (measureIvar->getName() == measure->getName()) {
                return streamVar;
            }
        }
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void ConfiguratorStreamsUIHandler::addNewMeasureToStream(CVariableStream *stream)
{
    Q_ASSERT(stream);

    QString label;
    if (!enterText(label, tr("New measure label")))
        return;

    const QString tempName = CVariableFactory::buildTemporaryName("Measure");
    IVariable *varMeasure = CVariableFactory::buildTemporary(stream->getAutomate(), this, tempName, e_type_measure);
    Q_ASSERT(varMeasure);

    varMeasure->setLabel(label);
    stream->addMeasure(varMeasure);
}

void ConfiguratorStreamsUIHandler::slotItemClicked()
{
    CPushButton *item = qobject_cast<CPushButton *>(sender());
    Q_ASSERT(item);

    IVariable *ivar = getVariable(item->userData().toString());
    Q_ASSERT(ivar);

    QString label = ivar->getLabel();
    if (!enterText(label, tr("New label (%1)").arg(label)))
        return;

    ivar->setLabel(label);

    // SERES_TODO: Changing a measure (or adding/removing) from stream should trigger streams updated signal
    // KDAB_TODO remove once the automat is connected to the measure
    layout();
}

void ConfiguratorStreamsUIHandler::slotAddItem()
{
    CToolButton *item = qobject_cast<CToolButton *>(sender());
    Q_ASSERT(item);

    CVariableStream *varStream = qobject_cast<CVariableStream *>(getVariable(item->userData().toString()));
    Q_ASSERT(varStream);

    addNewMeasureToStream(varStream);

    // SERES_TODO: Changing a measure (or adding/removing) from stream should trigger streams updated signal
    // KDAB_TODO remove once the automat is connected to the measure
    layout();
}

void ConfiguratorStreamsUIHandler::slotAddStreams()
{
    //select stream name and create it
    QString label;
    if (!enterText(label, tr("New stream label")))
        return;

    const QString tempName = CVariableFactory::buildTemporaryName("Stream");
    CVariableStream *varStream = qobject_cast<CVariableStream *>(CVariableFactory::buildTemporary(m_automate, this, tempName, e_type_stream));

    varStream->setLabel(label);
    addNewMeasureToStream(varStream);


    m_automate->addStream(varStream, true);
}


