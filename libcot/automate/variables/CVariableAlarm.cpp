#include "CVariableAlarm.h"
#include "CAutomate.h"
#include "CModelExtensionCard.h"
#include "IOrgan.h"
#include "ICom.h"
#include "CUnit.h"
#include "qdebug.h"
CVariableAlarm::CVariableAlarm(QObject *parent)
    : CVariableOutputBool()
{

}

CVariableAlarm::~CVariableAlarm()
{

}

CVariableAlarm::CVariableAlarm(const QMap<QString, QVariant> &mapVar)
    : CVariableOutputBool(mapVar)
{
    connect(this, &CVariableAlarm::signalNewAlarm, CAutomate::getInstance(), &CAutomate::slotNewAlarm);
    connect(this, &CVariableAlarm::signalCancelAlarm, CAutomate::getInstance(), &CAutomate::slotCancelAlarm);
    m_passive = mapVar.value(QStringLiteral("passive")).toBool(); //false par défaut même si il n'y a de champs passive dans le json
}

void CVariableAlarm::writeValue(){
    if(m_passive)
        m_organ->getExtCard()->getICom()->writeData(m_value, this->getOrganAddr());
    else
        m_organ->getExtCard()->getICom()->writeData(!m_value, this->getOrganAddr());
}

 void CVariableAlarm::setValue(bool arg_value){
     if(!m_value && m_value != arg_value) //si mise en alarme et pas déjà en alarme
         emit signalNewAlarm(this);
     else if(m_value && m_value != arg_value)
         emit signalCancelAlarm(this);

     CVariableOutputBool::setValue(arg_value);
 }


enumVariableType CVariableAlarm::getType()const{
    return e_type_alarm;
}
IVariable* CVariableAlarm::getIVariable(){
    return this;
}
enumAlarmType CVariableAlarm::getAlarmType(){
    return m_alarmType;
}

QVariantMap CVariableAlarm::serialize(){
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("alarm"));
    mapSerialise.insert(QStringLiteral("value"), m_value);

    if(m_organ->getName() != QStringLiteral("unknown_organ")){
        mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
        mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    }
    return mapSerialise;
}
enumVariableOrganType CVariableAlarm::getOrganType() const {
    return e_type_organ_output;
}
