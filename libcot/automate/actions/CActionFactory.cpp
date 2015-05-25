#include "CActionFactory.h"
#include "CActionCmdPompe.h"
#include "CActionCmdRelay.h"
#include "CActionCmdReadInput.h"
#include "CActionBlock.h"
#include "CActionUnknow.h"

#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"


IAction* CActionFactory::build(const QVariantMap &mapAction){

    IAction* action = Q_NULLPTR;
    const QString type = mapAction[QStringLiteral("type")].toString();
    if(type == QStringLiteral("cmd_pump")){
        action = new CActionCmdPompe(mapAction);
    }
    else if(type == QStringLiteral("cmd_relay")){
        action = new CActionCmdRelay(mapAction);
    }
    else if(type == QStringLiteral("cmd_read_input")){
        action = new CActionCmdReadInput(mapAction);
    }
    else if(type == QStringLiteral("block")){
        action = new CActionBlock(mapAction);
    }
    else{
        action = new CActionUnknow(mapAction);
        qCDebug(COTAUTOMATE_LOG) << "Classe action INCONNUE :" << type;
    }

    return action;
}

IAction* CActionFactory::build(actionType arg_type){
    IAction* action = Q_NULLPTR;
    switch(arg_type){
    case actionType::type_block:
        action = new CActionBlock();
        break;

    case actionType::type_cmd_pump:
        action = new CActionCmdPompe();
        break;

    case actionType::type_cmd_read_input:
        action = new CActionCmdReadInput();
        break;

    case actionType::type_cmd_relay:
        action = new CActionCmdRelay();
        break;

    default:
        action = new CActionUnknow();
        qCDebug(COTAUTOMATE_LOG) << "Classe action INCONNUE :" << arg_type;
        break;

    }
    return action;

}
