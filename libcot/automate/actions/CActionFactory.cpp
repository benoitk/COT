#include "CActionFactory.h"
#include "CActionCmdPompe.h"
#include "CActionCmdDigitalOutput.h"
#include "CActionCmdReadInput.h"
#include "CActionBlock.h"
#include "CActionUnknow.h"
#include "CActionTest.h"
#include "CActionAcquisitionCitNpoc.h"
#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"


IAction* CActionFactory::build(const QVariantMap &mapAction, QObject *parent){

    IAction* action = Q_NULLPTR;
    const QString type = mapAction[QStringLiteral("type")].toString();
    if(type == QStringLiteral("cmd_pump")){
        action = new CActionCmdPompe(mapAction,parent);
    }
    else if(type == QStringLiteral("cmd_digital_output")){
        action = new CActionCmdDigitalOutput(mapAction,parent);
    }
    else if(type == QStringLiteral("cmd_read_input")){
        action = new CActionCmdReadInput(mapAction,parent);
    }
    else if(type == QStringLiteral("block")){
        action = new CActionBlock(mapAction,parent);
    }
    else if(type == QStringLiteral("test")){
        action = new CActionTest(mapAction,parent);
    }
    else if(type == QStringLiteral("acquisition_cit_npoc")){
        action = new CActionAcquisitionCitNpoc(mapAction,parent);
    }
    else{
        action = new CActionUnknow(mapAction,parent);
        qCDebug(COTAUTOMATE_LOG) << "Classe action INCONNUE :" << type;
    }

    return action;
}

IAction* CActionFactory::build(actionType arg_type, QObject* parent){
    IAction* action = Q_NULLPTR;
    switch(arg_type){
    case actionType::type_block:
        action = new CActionBlock(QVariantMap(), parent);
        break;

    case actionType::type_cmd_pump:
        action = new CActionCmdPompe(QVariantMap(), parent);
        break;

    case actionType::type_cmd_read_input:
        action = new CActionCmdReadInput(QVariantMap(), parent);
        break;

    case actionType::type_cmd_digital_output:
        action = new CActionCmdDigitalOutput(QVariantMap(), parent);
        break;

    case actionType::type_test:
        action = new CActionTest(QVariantMap(), parent);
        break;

    default:
        action = new CActionUnknow(QVariantMap(), parent);
        qCDebug(COTAUTOMATE_LOG) << "Classe action INCONNUE :" << arg_type;
        break;

    }
    return action;

}
