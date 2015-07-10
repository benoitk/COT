#include "CEditVariableTabUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CPushButton.h"

#include <CAutomate.h>
#include <CVariableStream.h>
#include <CVariableMeasure.h>

CEditVariableTabUIHandler::CEditVariableTabUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableIVariableDescriber(this));
}

CEditVariableTabUIHandler::~CEditVariableTabUIHandler()
{
}

void CEditVariableTabUIHandler::layout(IVariable *ivar)
{
    describer()->describe(QVariant::fromValue(ivar));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}

void CEditVariableTabUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    IConfiguratorUIHandler::rowChanged(row, ivar);

    if (ivar->getName() == "streamOrMeasure") {
        const CAutomate *automate = CAutomate::getInstance();
        QWidget *editor = row.widgetAt<QWidget *>(1);
        CVariableStream *stream = automate->getStream(ivar->toString());
        CVariableMeasure *measure = automate->getMeasure(ivar->toString());

        if (measure) {
            stream = automate->getMeasureStream(measure);
            QStringList texts;

            if (stream) {
                texts << stream->getLabel();
            }

            texts << measure->getLabel();

            qobject_cast<CPushButton *>(editor)->setText(texts.join(" / "));
        }
        else if (stream) {
            qobject_cast<CPushButton *>(editor)->setText(stream->getLabel());
        }
    }
}

/*

*/
