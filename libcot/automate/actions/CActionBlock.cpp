#include "CActionBlock.h"
#include "IVariable.h"
#include "CAutomate.h"
#include "CCycleAutonome.h"
#include "cotautomate_debug.h"

CActionBlock::CActionBlock(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    m_cycle = new CCycleAutonome(mapAction, this);
}

CActionBlock::~CActionBlock()
{

}

CCycleAutonome* CActionBlock::getCycle(){
    return m_cycle;
}

bool CActionBlock::runAction(){
    qCDebug(COTAUTOMATE_LOG) << "Running action block" << getName();
    m_cycle->slotRunCycle();

    return true;
}




QList<IVariable*> CActionBlock::getListParameters()const{
    QList<IVariable*> listParams;
    return listParams;
}

actionType CActionBlock::getType()const {
    return actionType::type_block;
}
bool CActionBlock::variableUsed(IVariable *)const {
    //bool bReturn = false;
    //foreach(IAction* action, m_listAction){if(action->variableUsed()) bReturn=true;}
    return false;
}

QMap<QString, IVariable*> CActionBlock::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}

QMap<QString, IVariable*> CActionBlock::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionBlock::setParameter(const QString& arg_key, IVariable* arg_parameter){
//    if(tr("Setpoint")== arg_key) m_setpoint= arg_parameter;

//    else if(tr("Generate critical error")== arg_key)m_criticalError->setValue(arg_parameter->toBool());
}
variableType CActionBlock::getWaitedType(const QString& arg_key){
   //peu importe

    return type_unknow;
}
