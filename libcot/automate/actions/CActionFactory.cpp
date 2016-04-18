#include "CActionFactory.h"
#include "CActionCmdPompe.h"
#include "CActionCmdDigitalOutput.h"
#include "CActionCmdReadInput.h"
#include "CActionDCEngine.h"
#include "CActionBlock.h"
#include "CActionUnknow.h"
#include "CActionTest.h"
#include "CActionRewriteOutput.h"
#include "CActionAcquisitionCitNpoc.h"
#include "CActionCalibrationCalcul.h"
#include "CActionCmd420.h"
#include "CActionSum.h"
#include "CActionCopy.h"
#include "CActionFindClosestFromReference.h"
#include "CActionFindBiggerValue.h"
#include "CActionSlope.h"

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
    else if(type == QStringLiteral("cmd_dc_engine")){
        action = new CActionDCEngine(mapAction,parent);
    }
    else if(type == QStringLiteral("rewrite_output")){
        action = new CActionRewriteOutput(mapAction,parent);
    }
    else if(type == QStringLiteral("calibration_calcul")){
        action = new CActionCalibrationCalcul(mapAction,parent);
    }
    else if(type == QStringLiteral("cmd_loop_4_20")){
        action = new CActionCmd420(mapAction,parent);
    }
    else if(type == QStringLiteral("sum")){
        action = new CActionSum(mapAction,parent);
    }
    else if(type == QStringLiteral("find_closest_from_reference")){
        action = new CActionFindClosestFromReference(mapAction,parent);
    }
    else if(type == QStringLiteral("find_bigger_value")){
        action = new CActionFindBiggerValue(mapAction,parent);
    }
    else if(type == QStringLiteral("slope")){
        action = new CActionSlope(mapAction,parent);
    }
    else if(type == QStringLiteral("copy")){
        action = new CActionCopy(mapAction,parent);
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
