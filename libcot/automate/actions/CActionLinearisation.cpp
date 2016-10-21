#include "CActionLinearisation.h"

#include "CActionLinearisation.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "IVariableInput.h"
#include "CVariableCurve.h"
#include "cotautomate_debug.h"
//#include "qmath.h"

#include "qthreadpool.h"


CActionLinearisation::CActionLinearisation(const QVariantMap &mapAction, CAutomate *parent)
    : IAction(mapAction, parent)
{

   m_rawValue = m_automate->getVariable(mapAction[QStringLiteral("raw_value")].toString());
   m_value = m_automate->getVariable(mapAction[QStringLiteral("value")].toString());
   m_curve = Q_NULLPTR;
   if(m_automate->getVariable(mapAction[QStringLiteral("curve")].toString())->getType() == e_type_curve)
        m_curve = dynamic_cast<CVariableCurve*>(m_automate->getVariable(mapAction[QStringLiteral("curve")].toString()));


     //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
     this->setAutoDelete(false);
}


QVariantMap CActionLinearisation::serialize(){
    QVariantMap mapSerialize = IAction::serialize();

    mapSerialize.insert(QStringLiteral("raw_value"), m_rawValue->getName());
    mapSerialize.insert(QStringLiteral("value"), m_value->getName());
    mapSerialize.insert(QStringLiteral("curve"), m_curve->getName());



    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("linearisation"));
    return mapSerialize;
}

bool CActionLinearisation::runAction(ICycle* arg_stepParent){
    IAction::runAction(arg_stepParent);

    QThreadPool* threadPool = QThreadPool::globalInstance();
    bool result = threadPool->tryStart(this);
    if(!result && (threadPool->maxThreadCount() ==  threadPool->activeThreadCount())){
        qDebug() << "max " << threadPool->maxThreadCount() << " current " << threadPool->activeThreadCount();
        threadPool->setMaxThreadCount(threadPool->maxThreadCount()+1);
        result = QThreadPool::globalInstance()->tryStart(this);
        if(!result){
            qDebug() << "can't start thread in CActionLinearisation::runAction";
        }
    }
    return true;
}



void CActionLinearisation::run(){
    ICycle* stepParent = getStepParent();
    qCDebug(COTAUTOMATE_LOG)<< "CActionLinearisation 'qrunnable' ";

    if(m_curve){
        m_value->setValue( m_curve->getLiearisedY(m_rawValue->toFloat()) );
    }

    emit signalActionFinished(this);
}

bool CActionLinearisation::waitUntilFinished(){
    return false;
}

QList<IVariable*> CActionLinearisation::getListParameters()const{
    QList<IVariable*> listParams;


    return listParams;
}
actionType CActionLinearisation::getType()const {
    return actionType::type_linearisation;
}

bool CActionLinearisation::variableUsed(IVariable *arg_var)const {

    return false;
}

QMap<QString, IVariable*> CActionLinearisation::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;

    map.insert(tr("Raw value"), m_rawValue);
    map.insert(tr("Value"), m_value);
    map.insert(tr("Curve"), m_curve);




    return map;
}

QMap<QString, IVariable*> CActionLinearisation::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionLinearisation::setParameter(const QString& arg_key, IVariable* arg_parameter){
    if(tr("Raw value")== arg_key)m_rawValue= arg_parameter;
    else if(tr("Value")== arg_key)m_value= arg_parameter;



}
enumVariableType CActionLinearisation::getWaitedType(const QString& arg_key){
    if(tr("Raw value")== arg_key) return e_type_float;
    else if(tr("Value")== arg_key)return e_type_float;
    else if(tr("Curve")== arg_key)return e_type_float;

    return e_type_unknow;
}
