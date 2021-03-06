#include "CVariableAlarm.h"
#include "CAutomate.h"
#include "CModelExtensionCard.h"
#include "IOrgan.h"
#include "ICom.h"
#include "CUnit.h"
#include "qdebug.h"
CVariableAlarm::CVariableAlarm(CAutomate* arg_automate, QObject *parent)
    : CVariableOutputBool(arg_automate, parent)
{

}

CVariableAlarm::~CVariableAlarm()
{

}

CVariableAlarm::CVariableAlarm(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject* parent)
    : CVariableOutputBool(mapVar, arg_automate, parent)
{
    connect(this, &CVariableAlarm::signalNewAlarm, m_automate, &CAutomate::slotNewAlarm);
    connect(this, &CVariableAlarm::signalAquitedAlarm, m_automate, &CAutomate::slotAcquitedAlarm);
    connect(this, &CVariableAlarm::signalStillInAlarm, m_automate, &CAutomate::slotStillInAlarm);
    connect(m_automate, &CAutomate::signalAquitAllAlarm, this, &CVariableAlarm::slotAcquit);
    QString alarmType = mapVar.value(QStringLiteral("alarm_type")).toString();

    if(alarmType == QStringLiteral("not_critical_error_skip_cycle_try_again")) m_alarmType = e_not_critical_error_skip_cycle_try_again;
    else if(alarmType == QStringLiteral("critical_error_stop_cycle")) m_alarmType = e_critical_error_stop_cycle;
    else m_alarmType = e_warning_do_nothing; //"warning_do_nothing"
//    m_alarmType = e_warning_do_nothing; //"warning_do_nothing"

    m_autoAcquit = mapVar.value(QStringLiteral("auto_acquit")).toBool();
    m_numUntilSetAlarm = mapVar.value(QStringLiteral("delay")).toInt() -1;
    m_nbSkipBeforeStopCycle = mapVar.value(QStringLiteral("nb_skip_before_stop_cycle")).toInt()-1;
    m_inhibited = false;
    m_countUntilSetAlarm = m_numUntilSetAlarm;
    m_countSkipBeforeStopCycle = m_nbSkipBeforeStopCycle;
}

void CVariableAlarm::setInhibited(bool arg){
    m_inhibited = arg;
}
QString CVariableAlarm::toString(){
    if(m_value)
        return tr("levée");
    return tr("acquitée");
}

void CVariableAlarm::deconnectFromAutomate(){
    disconnect(this, &CVariableAlarm::signalNewAlarm, m_automate, &CAutomate::slotNewAlarm);
    disconnect(this, &CVariableAlarm::signalAquitedAlarm, m_automate, &CAutomate::slotAcquitedAlarm);
    disconnect(this, &CVariableAlarm::signalStillInAlarm, m_automate, &CAutomate::slotStillInAlarm);
}

void CVariableAlarm::connectFromAutomate(){
    connect(this, &CVariableAlarm::signalNewAlarm, m_automate, &CAutomate::slotNewAlarm);
    connect(this, &CVariableAlarm::signalAquitedAlarm, m_automate, &CAutomate::slotAcquitedAlarm);
    connect(this, &CVariableAlarm::signalStillInAlarm, m_automate, &CAutomate::slotStillInAlarm);
}

 void CVariableAlarm::setValue(bool arg_value){
     this->setValue(arg_value, false);
 }

 void CVariableAlarm::setValue(bool arg_value, bool arg_forceAcquit){
     if(!m_inhibited){
         if(!m_value && m_value != arg_value && m_countUntilSetAlarm-- < 0){ //si mise en alarme et pas déjà en alarme
             emit signalNewAlarm(this);
             CVariableOutputBool::setValue(arg_value);
             m_countUntilSetAlarm = m_numUntilSetAlarm;
         }
         else if(m_value && m_value != arg_value && (m_autoAcquit|arg_forceAcquit)){
             emit signalAquitedAlarm(this);
             CVariableOutputBool::setValue(arg_value);
             m_countUntilSetAlarm = m_numUntilSetAlarm;
         }
         else if(m_value && m_value == arg_value && m_countUntilSetAlarm-- < 0){
             if(m_alarmType == e_not_critical_error_skip_cycle_try_again)
             {
                 m_countSkipBeforeStopCycle--;
             }
             m_countUntilSetAlarm = m_numUntilSetAlarm;
             emit signalStillInAlarm(this);
         }
     }

 }
void CVariableAlarm::setToBindedValue(const QVariant & arg_value){
    //m_passive = false -> garde l'état; true -> inverse l'état
    if(!m_value && m_value != arg_value && m_countUntilSetAlarm-- < 0){ //si mise en alarme et pas déjà en alarme
        emit signalNewAlarm(this);
        CVariableOutputBool::setToBindedValue(arg_value);
        m_countUntilSetAlarm = m_numUntilSetAlarm;
    }
    else if(m_value && m_value != arg_value && m_autoAcquit){
        emit signalAquitedAlarm(this);
        CVariableOutputBool::setToBindedValue(arg_value);
        m_countUntilSetAlarm = m_numUntilSetAlarm;
    }
    else if(m_value && m_value == arg_value && m_countUntilSetAlarm-- < 0){
        m_countSkipBeforeStopCycle--;
        m_countUntilSetAlarm = m_numUntilSetAlarm;
        emit signalStillInAlarm(this);
    }
}
bool CVariableAlarm::haveToStopAfterToMuchSkip(){
    if(m_countSkipBeforeStopCycle < 0)
        return true;
    return false;
}
 void CVariableAlarm::slotAcquit(){
     m_countSkipBeforeStopCycle = m_nbSkipBeforeStopCycle;
     setValue(false, true);
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
    QVariantMap mapSerialise = CVariableOutputBool::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("alarm"));

//    if(m_organ->getName() != QStringLiteral("unknown_organ")){
//        mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
//        mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
//    }

    QString alarmType;
    switch(m_alarmType){
    case e_not_critical_error_skip_cycle_try_again:
        alarmType = QStringLiteral("not_critical_error_skip_cycle_try_again");
        break;
    case e_critical_error_stop_cycle:
        alarmType = QStringLiteral("critical_error_stop_cycle");
        break;
    case e_warning_do_nothing:
    default:
        alarmType = QStringLiteral("warning_do_nothing");
        break;
    }
    mapSerialise.insert(QStringLiteral("alarm_type"), alarmType);
    mapSerialise.insert(QStringLiteral("auto_acquit"), m_autoAcquit);
    mapSerialise.insert(QStringLiteral("delay"), m_numUntilSetAlarm+1 );
    mapSerialise.insert(QStringLiteral("nb_skip_before_stop_cycle"), m_nbSkipBeforeStopCycle+1 );

    return mapSerialise;
}
enumVariableOrganType CVariableAlarm::getOrganType() const {
    return e_type_organ_output;
}
