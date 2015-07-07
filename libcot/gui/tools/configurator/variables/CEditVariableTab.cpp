#include "CEditVariableTab.h"
#include "CAutomate.h"
#include "CEditVariableTabUIHandler.h"
#include "IConfiguratorUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <CUnit.h>
#include <IOrgan.h>

CEditVariableTab::CEditVariableTab(QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    m_configuratorUIHandler = new CEditVariableTabUIHandler(scrollableWidget(), this);
    initBaseTab();
}

void CEditVariableTab::setVariables(IVariable *ivar)
{
    m_configuratorUIHandler->layout(ivar);
}

void CEditVariableTab::applyProperties(const QVariant &object)
{
    const IVariableObjectDescriber *describer = m_configuratorUIHandler->describer();
    CAutomate * automate = CAutomate::getInstance();
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);

    ivar->setLabel(describer->getVariable(QStringLiteral("label"))->toString());
    ivar->setValue(describer->getVariable(QStringLiteral("value"))->toVariant());

    const QString unitName = describer->getVariable(QStringLiteral("unit"))->toString();
    CUnit *unit = automate->getUnit(unitName);
    if (ivar->getUnit() != unit) {
        ivar->switchToUnit(unit);
    }

    IVariable *organ = describer->getVariable(QStringLiteral("organ"));
    if (organ) {
        IOrgan *iorgan = automate->getOrgan(organ->toString());

        switch (ivar->getOrganType()) {
            case type_organ_input: {
                IVariableInput *iivar = dynamic_cast<IVariableInput *>(ivar);
                Q_ASSERT(iivar);
                iivar->setOrgan(iorgan ? iorgan->getExtCard() : Q_NULLPTR, iorgan ? iorgan->getName() : QString());
                break;
            }

            case type_organ_output: {
                IVariableOutput *oivar = dynamic_cast<IVariableOutput *>(ivar);
                Q_ASSERT(oivar);
                oivar->setOrgan(iorgan ? iorgan->getExtCard() : Q_NULLPTR, iorgan ? iorgan->getName() : QString());
                break;
            }

            default:
                break;
        }
    }

    CVariableStream *stream = automate->getStream(describer->getVariable(QStringLiteral("streamOrMeasure"))->toString());
    CVariableMeasure *measure = automate->getMeasure(describer->getVariable(QStringLiteral("streamOrMeasure"))->toString());

    if (measure) {
        // SERES_TODO: need getVariableMeasure / changeVariableMeasure
        /*if (automate->getVariableMeasure(ivar) != measure) {
            automate->changeVariableMeasure(ivar, measure);
        }*/
    }
    else if (stream) {
        if (automate->getVariableStream(ivar) != stream) {
            automate->changeVariableStream(ivar, stream);
        }
    }
    else {
        //automate->changeVariableMeasure(ivar, Q_NULLPTR); // SERES_TODO
        automate->changeVariableStream(ivar, Q_NULLPTR);
    }
}

