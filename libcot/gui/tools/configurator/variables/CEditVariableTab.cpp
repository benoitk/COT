#include "CEditVariableTab.h"
#include "CAutomate.h"
#include "CEditVariableTabUIHandler.h"
#include "IConfiguratorUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <CUnit.h>
#include <IOrgan.h>

CEditVariableTab::CEditVariableTab(CAutomate* arg_automate, IVariable *ivar, QWidget *parent)
    : IConfiguratorEditTab(parent)
    , m_handler(new CEditVariableTabUIHandler(arg_automate, scrollableWidget(), this))
    , m_automate(arg_automate)
{
    Q_ASSERT(ivar);
    m_handler->layout(ivar);
    initBaseTab();
}

void CEditVariableTab::applyProperties(const QVariant &object)
{
    const IVariableObjectDescriber *describer = m_handler->describer();
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);

    ivar->setLabel(describer->getVariable(QStringLiteral("label"))->toString());
    ivar->setValue(describer->getVariable(QStringLiteral("value"))->toVariant());

    const QString unitName = describer->getVariable(QStringLiteral("unit"))->toString();
    CUnit *unit = m_automate->getUnit(unitName);
    if (ivar->getUnit() != unit) {
        ivar->switchToUnit(unit);
    }

    IVariable *organ = describer->getVariable(QStringLiteral("organ"));
    if (organ) {
        IOrgan *iorgan = m_automate->getOrgan(organ->toString());

        switch (ivar->getOrganType()) {
            case e_type_organ_input: {
                IVariableInput *iivar = dynamic_cast<IVariableInput *>(ivar);
                Q_ASSERT(iivar);
                iivar->setOrgan(iorgan ? iorgan->getExtCard() : Q_NULLPTR, iorgan ? iorgan->getName() : QString());
                break;
            }

            case e_type_organ_output: {
                IVariableOutput *oivar = dynamic_cast<IVariableOutput *>(ivar);
                Q_ASSERT(oivar);
                oivar->setOrgan(iorgan ? iorgan->getExtCard() : Q_NULLPTR, iorgan ? iorgan->getName() : QString());
                break;
            }

            default:
                break;
        }
    }

    CVariableStream *stream = m_automate->getStream(describer->getVariable(QStringLiteral("streamOrMeasure"))->toString());
    CVariableMeasure *measure = m_automate->getMeasure(describer->getVariable(QStringLiteral("streamOrMeasure"))->toString());

    if (measure) {
        if (m_automate->getVariableMeasure(ivar) != measure) {
            m_automate->changeVariableMeasure(ivar, measure);
        }
    }
    else if (stream) {
        if (m_automate->getVariableStream(ivar) != stream) {
            m_automate->changeVariableStream(ivar, stream);
        }
    }
    else {
        m_automate->changeVariableMeasure(ivar, Q_NULLPTR);
        m_automate->changeVariableStream(ivar, Q_NULLPTR);
    }
}

