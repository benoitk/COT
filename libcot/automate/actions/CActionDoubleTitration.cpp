#include "CActionDoubleTitration.h"
#include "IVariable.h"
#include "CVariableAlarm.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "CVariableCurve.h"
#include "IVariableInput.h"
#include "cotautomate_debug.h"
//#include "qmath.h"

#include "qelapsedtimer.h"
#include "qthreadpool.h"

CActionDoubleTitration::CActionDoubleTitration(const QVariantMap &mapAction, CAutomate *parent)
    : IAction(mapAction, parent)
{

    m_measureCell = m_automate->getVariable(mapAction[QStringLiteral("cellule")].toString());
    m_timeFirstInflection = m_automate->getVariable(mapAction[QStringLiteral("result")].toString());
    m_timeout = m_automate->getVariable(mapAction[QStringLiteral("timeout")].toString());
    m_waitUntilFinished = mapAction[QStringLiteral("wait_until_finished")].toBool();



    m_alimPump = Q_NULLPTR;
    m_runOrStopPump = Q_NULLPTR;
    m_clockwisePump = Q_NULLPTR;
    m_speedPump = Q_NULLPTR;
    m_OriginReturnPump = Q_NULLPTR;
    m_defaultPump = Q_NULLPTR;
    m_alarmPump = Q_NULLPTR;
    if(m_automate->getVariable(mapAction[QStringLiteral("alim")].toString())->getOrganType() == e_type_organ_output)
        m_alimPump = dynamic_cast<CVariableOutputBool*>(m_automate->getVariable(mapAction[QStringLiteral("alim")].toString()));
    if(m_automate->getVariable(mapAction[QStringLiteral("nbr_turns")].toString())->getOrganType() == e_type_organ_output)
        m_runOrStopPump = dynamic_cast<CVariableOutputBool*>(m_automate->getVariable(mapAction[QStringLiteral("nbr_turns")].toString()));
    if(m_automate->getVariable(mapAction[QStringLiteral("clockwise")].toString())->getOrganType() == e_type_organ_output)
        m_clockwisePump =  dynamic_cast<CVariableOutputBool*>(m_automate->getVariable(mapAction[QStringLiteral("clockwise")].toString()));
    if(m_automate->getVariable(mapAction[QStringLiteral("speed")].toString())->getOrganType() == e_type_organ_output)
        m_speedPump =dynamic_cast<CVariableOutputInt*>( m_automate->getVariable(mapAction[QStringLiteral("speed")].toString()));
    if(m_automate->getVariable(mapAction[QStringLiteral("origin_return_before")].toString())->getOrganType() == e_type_organ_output)
        m_OriginReturnPump = dynamic_cast<CVariableOutputBool*>(m_automate->getVariable(mapAction[QStringLiteral("origin_return_before")].toString()));
    if(m_automate->getVariable(mapAction[QStringLiteral("default")].toString())->getOrganType() == e_type_organ_input)
        m_defaultPump = dynamic_cast<CVariableInputBool*>(m_automate->getVariable(mapAction[QStringLiteral("default")].toString()));
    if(m_automate->getVariable(mapAction[QStringLiteral("alarm")].toString())->getOrganType() == e_type_organ_output)
        m_alarmPump = dynamic_cast<CVariableAlarm*>(m_automate->getVariable(mapAction[QStringLiteral("alarm")].toString()));

    //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
    this->setAutoDelete(false);
}

QVariantMap CActionDoubleTitration::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("cellule"), m_measureCell->getName());
    mapSerialize.insert(QStringLiteral("result"), m_timeFirstInflection->getName());
    mapSerialize.insert(QStringLiteral("zero_point"), m_timeSecondInflection->getName());

    mapSerialize.insert(QStringLiteral("timeout"), m_timeout->getName());
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("acquisition_cit_npoc"));
    return mapSerialize;
}

bool CActionDoubleTitration::runAction(ICycle* arg_stepParent){
    IAction::runAction(arg_stepParent);

    QThreadPool* threadPool = QThreadPool::globalInstance();
    bool result = threadPool->tryStart(this);
    if(!result && (threadPool->maxThreadCount() ==  threadPool->activeThreadCount())){
        qDebug() << "max " << threadPool->maxThreadCount() << " current " << threadPool->activeThreadCount();
        threadPool->setMaxThreadCount(threadPool->maxThreadCount()+1);
        result = QThreadPool::globalInstance()->tryStart(this);
        if(!result){
            qDebug() << "can't start thread in CActionDoubleTitration::runAction";
        }
    }
    return true;
}

void CActionDoubleTitration::run(){
    ICycle* stepParent = getStepParent();
    qCDebug(COTAUTOMATE_LOG)<< "CActionDoubleTitration 'qrunnable' ";
    QString sActionInfo;

    bool bFirstInflectionPointDone  = false;
    bool bSecondInflectionPointDone = false;

    float fCurrentDelta = 0;
    float fDeltaMax = 0;
    float fTimeDeltaMax = 0;
    float fCurrentMeasure = 0;
    float fPreviousMeasure = 0;


    QElapsedTimer timer;
    IVariableInput* measureCell = Q_NULLPTR;
    if(m_measureCell->getOrganType() == e_type_organ_input)
        measureCell = dynamic_cast<IVariableInput*>(m_measureCell);
    if(!measureCell){
        //TODO mettre une alarme au cas ou la célule de mesure soit mal configurée
        return;
    }

    //ligne de base
    fPreviousMeasure = measureCell->readValue()->toFloat();

    //Configuration de la pompe
    if(m_alimPump && m_OriginReturnPump && m_clockwisePump  && m_speedPump){
        if(!m_alimPump->toBool()) m_alimPump->setValue(true);

        m_alimPump->writeValue();
        QThread::msleep(5);

        m_clockwisePump->writeValue();
        QThread::msleep(5);

        m_speedPump->writeValue();
        QThread::msleep(5);

        //Vérification de m_alarmPump et m_defaultPump ici au cas ou l'utilisateur ne souhaite pas utiliser le defaut pompe
        if(m_alarmPump && m_defaultPump){
            bool bDefault = m_defaultPump->readValue()->toBool();
            if(bDefault){
                m_alarmPump->setValue(bDefault);
                emit signalActionFinished(this);
                return;
            }
        }
    }

    //Démarage pompe en continu
    m_runOrStopPump->setValue(true);

    //démarage chrono pour les points d'inflection
    timer.start();

    QList<QPair<qint64, float>> listPairTimeDelta;
    while(!bFirstInflectionPointDone && !bSecondInflectionPointDone){
        fCurrentMeasure = measureCell->readValue()->toFloat();
        //Si l'echatillonage donne une nouvelle mesure
        if(fCurrentMeasure != fPreviousMeasure){
          fCurrentDelta = fabs(fCurrentMeasure - fPreviousMeasure);
          listPairTimeDelta.append(QPair<qint64, float>(timer.elapsed(),fCurrentDelta));
        }
        QThread::msleep(200);
    }
    m_runOrStopPump->setValue(false);

    QPair<qint64, float> pair;
    foreach (pair, listPairTimeDelta) {
        if(pair.second > fDeltaMax)
            fTimeDeltaMax = pair.first;
    }
    m_timeFirstInflection->setValue(fTimeDeltaMax);

    updateActionInfos(m_label + tr(" finished"), stepParent);
    emit signalActionFinished(this);
}

bool CActionDoubleTitration::waitUntilFinished(){
    return m_waitUntilFinished;
}

QList<IVariable*> CActionDoubleTitration::getListParameters()const{
    QList<IVariable*> listParams;
    return listParams;
}
actionType CActionDoubleTitration::getType()const {
    return actionType::type_acquisition_cit_npoc;
}

bool CActionDoubleTitration::variableUsed(IVariable *arg_var)const {
    if(m_measureCell == arg_var) return true;
    return false;
}

QMap<QString, IVariable*> CActionDoubleTitration::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}

QMap<QString, IVariable*> CActionDoubleTitration::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionDoubleTitration::setParameter(const QString& arg_key, IVariable* arg_parameter){


}
enumVariableType CActionDoubleTitration::getWaitedType(const QString& arg_key){
    if(tr("Cellule")== arg_key) return e_type_float;
    else if(tr("Zero point")== arg_key) return e_type_float;
    else if(tr("Result")== arg_key) return e_type_float;
    else if(tr("Air flow")== arg_key)return e_type_float;
    else if(tr("Vessel volume")== arg_key)return e_type_float;
    else if(tr("Coefficient 1")== arg_key)return e_type_float;
    else if(tr("Coefficient 2")== arg_key)return e_type_float;
    else if(tr("Coefficient 3")== arg_key)return e_type_float;
    else if(tr("Coefficient 4")== arg_key)return e_type_float;
    else if(tr("Coefficient 5")== arg_key)return e_type_float;
    else if(tr("Co2 ppmv to Co2 g/m3")== arg_key)return e_type_float;
    else if(tr("Time acquisition")== arg_key)return e_type_int;

    else if(tr("Generate critical error")== arg_key)return e_type_bool;

    return e_type_unknow;
}
