#include "CActionCmd420.h"

#include "IVariable.h"
#include "CVariableOutputInt.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"



CActionCmd420::CActionCmd420(const QVariantMap &mapAction, CAutomate *parent)
    : IAction(mapAction, parent)
{
    m_inputVar= m_automate->getVariable(mapAction[QStringLiteral("input_var")].toString());
    m_inputVarMin= m_automate->getVariable(mapAction[QStringLiteral("input_var_min")].toString());
    m_inputVarMax= m_automate->getVariable(mapAction[QStringLiteral("input_var_max")].toString());
    m_minAdjustement= m_automate->getVariable(mapAction[QStringLiteral("min_adjustement")].toString());
    m_maxAdjustement= m_automate->getVariable(mapAction[QStringLiteral("max_adjustement")].toString());

    m_outputVar = Q_NULLPTR;
    IVariable* tmp = m_automate->getVariable(mapAction[QStringLiteral("output_var")].toString());
    if(tmp->getOrganType() == e_type_organ_output && tmp->getType() == e_type_int){
        m_outputVar = dynamic_cast<CVariableOutputInt*>(tmp);
    }

}

QVariantMap CActionCmd420::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("cmd_loop_4_20"));
    mapSerialize.insert(QStringLiteral("input_var"), m_inputVar->getName());
    mapSerialize.insert(QStringLiteral("input_var_min"), m_inputVarMin->getName());
    mapSerialize.insert(QStringLiteral("input_var_max"), m_inputVarMax->getName());
    mapSerialize.insert(QStringLiteral("min_adjustement"), m_minAdjustement->getName());
    mapSerialize.insert(QStringLiteral("max_adjustement"), m_maxAdjustement->getName());
    if(m_outputVar)
        mapSerialize.insert(QStringLiteral("output_var"), m_outputVar->getName());
    return mapSerialize;
}

bool CActionCmd420::runAction(ICycle* arg_stepParent){
    qCDebug(COTAUTOMATE_LOG)<< "Action cmd 4-20 "
            << " label fr " << m_label
            << " Entrée " << m_inputVar->toString()
            << " Min adj " << m_minAdjustement->toString()
            << " Max adj " << m_maxAdjustement->toString();
    if(m_outputVar){
        qCDebug(COTAUTOMATE_LOG)<< "Output " << m_outputVar->toString();

        float fTemp = m_inputVar->toFloat();
        if (fTemp >= m_inputVarMax->toFloat()){
            m_outputVar->setValue(m_maxAdjustement->toInt());
        }
        else  if (fTemp <= m_inputVarMin->toFloat()){
            m_outputVar->setValue(m_minAdjustement->toInt());
        }
        else  if (m_inputVarMax->toFloat() > m_inputVarMin->toFloat()){
            //(short)( (m_ValMaxConvertisseur.nGetVal() - m_ValMinConvertisseur.nGetVal()) * (fTemp - m_AnalogZero.fGetVal()) / (m_AnalogPlage.fGetVal() - m_AnalogZero.fGetVal()) ) + m_ValMinConvertisseur.nGetVal()
            int result = ( (m_maxAdjustement->toInt() - m_minAdjustement->toInt()) * (fTemp - m_inputVarMin->toFloat())
                           / (m_inputVarMax->toFloat() - m_inputVarMin->toFloat()) ) + m_minAdjustement->toInt();
            m_outputVar->setValue(result) ;
        }
        else{
            m_outputVar->setValue(m_maxAdjustement->toInt());
        }

    }
    return true;
}

QList<IVariable*> CActionCmd420::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_inputVar);
    listParams.append(m_inputVarMin);
    listParams.append(m_inputVarMax);
    listParams.append(m_minAdjustement);
    listParams.append(m_maxAdjustement);
    listParams.append(m_outputVar);

    return listParams;
}
actionType CActionCmd420::getType()const {
    return actionType::type_cmd_420;
}

bool CActionCmd420::variableUsed(IVariable *arg_var)const {
    if(m_inputVar == arg_var) return true;
    if(m_inputVarMin == arg_var) return true;
    if(m_inputVarMax == arg_var) return true;
    if(m_minAdjustement == arg_var) return true;
    if(m_maxAdjustement == arg_var) return true;
    if(m_outputVar == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionCmd420::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("input_var"), m_inputVar);
    map.insert(tr("input_var_min"), m_inputVarMin);
    map.insert(tr("input_var_max"), m_inputVarMax);
    map.insert(tr("min_adjustement"), m_minAdjustement);
    map.insert(tr("max_adjustement"), m_maxAdjustement);
    map.insert(tr("output_var"), m_outputVar);
    return map;
}

QMap<QString, IVariable*> CActionCmd420::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionCmd420::setParameter(const QString& arg_key, IVariable* arg_parameter){
    if(tr("input_var")== arg_key)m_inputVar= arg_parameter;
    if(tr("input_var_min")== arg_key)m_inputVarMin= arg_parameter;
    if(tr("input_var_max")== arg_key)m_inputVarMax= arg_parameter;
    if(tr("min_adjustement")== arg_key)m_minAdjustement= arg_parameter;
    if(tr("max_adjustement")== arg_key)m_maxAdjustement= arg_parameter;

    if(tr("output_var")== arg_key
            && arg_parameter->getOrganType() == e_type_organ_output
            && arg_parameter->getType() == e_type_int)
        m_outputVar= dynamic_cast<CVariableOutputInt*>(arg_parameter);

}
enumVariableType CActionCmd420::getWaitedType(const QString& arg_key){
   //peu importe

    return e_type_unknow;
}
