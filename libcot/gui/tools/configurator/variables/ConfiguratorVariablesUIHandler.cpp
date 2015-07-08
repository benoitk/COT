#include "ConfiguratorVariablesUIHandler.h"
#include "CScrollablePagerWidget.h"
#include "CClickableLabel.h"
#include "cotgui_debug.h"

#include <CPushButton.h>
#include <CToolButton.h>
#include <CAutomate.h>
#include <CVariableFactory.h>
#include <CVariableMeasure.h>
#include <CVariableStream.h>

#include <QDebug>

ConfiguratorVariablesUIHandler::ConfiguratorVariablesUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
}

ConfiguratorVariablesUIHandler::~ConfiguratorVariablesUIHandler()
{
    CVariableFactory::deleteVariables(m_internalVariables);
}

void ConfiguratorVariablesUIHandler::layout()
{
    CVariableFactory::deleteVariables(m_internalVariables);

    CAutomate *automate = CAutomate::getInstance();
    //const IVariablePtrList streams = automate->getMapStreams().values();
    QList<CVariableStream*> streams = automate->getListStreams();
    IVariablePtrList ivars;
    QList<IVariable *> listVar;
    foreach ( CVariableStream *streamVar, streams) {
//        Q_ASSERT(streamIVar->getType() == type_stream);
//        CVariableStream *streamVar = static_cast<CVariableStream *>(streamIVar);

        ivars << streamVar;        
        ivars << streamVar->getListVariables();
        listVar << streamVar->getListVariables();

        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measureIvar);
            ivars << measureVar;
            ivars << measureVar->getListVariables();
            listVar << measureVar->getListVariables();
        }
    }
    // Add fake global stream
    IVariable *streamVar = CVariableFactory::buildTemporary(QString("fake_stream"), tr("Global"), type_stream);
    m_internalVariables[streamVar->getName()] = streamVar;
    ivars << streamVar;

    foreach( IVariable *var, automate->getMapVariables().values()) {
        if (!listVar.contains(var)) {
            ivars << var;
        }
    }

    IConfiguratorUIHandler::layout(ivars, false);
}

int ConfiguratorVariablesUIHandler::columnCount() const
{
    return 4;
}

IVariable *ConfiguratorVariablesUIHandler::getStreamOrMeasure(IVariable *ivar) const
{
    CAutomate *automate = CAutomate::getInstance();
//    const IVariablePtrList streams = automate->getMapStreams().values();
    const QList<CVariableStream*> streams = automate->getListStreams();
    foreach (CVariableStream *streamVar, streams) {
//        Q_ASSERT(streamIVar->getType() == type_stream);
//        CVariableStream *streamVar = static_cast<CVariableStream *>(streamIVar);
        if (streamVar->getListVariables().contains(ivar)) {
            return streamVar;
        }
        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measureIvar);
            if (measureVar->getListVariables().contains(ivar)) {
                return measureVar;
            }
        }
    }
    return Q_NULLPTR;
}

IVariable *ConfiguratorVariablesUIHandler::getVariable(const QString &name) const
{
    CAutomate *automate = CAutomate::getInstance();
    //    const IVariablePtrList streams = automate->getMapStreams().values();
    const QList<CVariableStream*> streams = automate->getListStreams();
    foreach (CVariableStream *streamVar, streams) {
    //        Q_ASSERT(streamIVar->getType() == type_stream);
    //        CVariableStream *streamVar = static_cast<CVariableStream *>(streamIVar);
        if (streamVar->getName() == name) {
            return streamVar;
        }

        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measureIvar);
            if (measureVar->getName() == name) {
                return measureVar;
            } else {
                foreach (IVariable *ivar, measureVar->getListVariables()) {
                    if (ivar->getName() == name) {
                        return ivar;
                    }
                }
            }
        }
    }

    return IVariableUIHandler::getVariable(name);
}


QWidget *ConfiguratorVariablesUIHandler::createWidget(int column, IVariable *ivar)
{

    const bool isStream = ivar && (ivar->getType() == type_stream);
    const bool isMeasure = ivar && (ivar->getType() == type_measure);
    const bool isVariable = !isStream && !isMeasure;
    IVariable *varParent = isVariable ? getStreamOrMeasure(ivar) : Q_NULLPTR;
    switch(column) {
    case 0:
        if (isStream) {
            return newLabel(ivar);
        }
        break;
    case 1:
        if ((isVariable && !varParent) || (isVariable && (varParent->getType() == type_stream))) {
            return newButton(ivar);
        } else if (isMeasure) {
            return newLabel(ivar);
        }
        break;
    case 2:
        if (isVariable && varParent && (varParent->getType() == type_measure)) {
            return newButton(ivar);
        } else if (!isStream && !isMeasure) {
            return newDeleteButton(ivar);
        }
        break;
    case 3:
        if (isVariable && varParent && (varParent->getType() == type_measure)) {
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
    const bool isStream = ivar && (ivar->getType() == type_stream);
    const bool isMeasure = ivar && (ivar->getType() == type_measure);
    //const bool isVariable = !isStream && !isMeasure;
    //IVariable *varParent = isVariable ? getStreamOrMeasure(ivar) : Q_NULLPTR;

    if (isStream) {
        row.widgetAt<CClickableLabel *>(0)->setText(ivar->getLabel());
    } else if (isMeasure) {
        row.widgetAt<CClickableLabel *>(1)->setText(ivar->getLabel());
    } else {
     CPushButton *button = row.widgetAt<CPushButton *>(1);
     if (!button) {
         button = row.widgetAt<CPushButton *>(2);
     }
     if (button)
         button->setText(ivar->getLabel());
    }
}

void ConfiguratorVariablesUIHandler::rowAboutToBeDeleted(const Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    CAutomate *automate = CAutomate::getInstance();
    automate->delVariable(ivar);
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
