#include "CEditVariableTabUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CPushButton.h"

#include <CAutomate.h>
#include <CVariableStream.h>
#include <CVariableMeasure.h>

CEditVariableTabUIHandler::CEditVariableTabUIHandler(CAutomate* arg_automate,CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(arg_automate, scrollable, parent)
    , m_automate(arg_automate)
{
    setDescriber(new CVariableIVariableDescriber(arg_automate, this));
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
        QWidget *editor = row.widgetAt<QWidget *>(1);
        CVariableStream *stream = m_automate->getStream(ivar->toString());
        CVariableMeasure *measure = m_automate->getMeasure(ivar->toString());

        if (measure) {
            stream = m_automate->getMeasureStream(measure);
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
