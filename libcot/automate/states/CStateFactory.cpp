//#include "CStateFactory.h"

//#include "IState.h"
//#include "CStateBlankCycleRunning.h"
//#include "CStateCyclePaused.h"
//#include "CStateCycleRunning.h"
//#include "CStateMaintenance.h"
//#include "CStateStopped.h"
//#include "CStateUnknow.h"'

//#include "qvariant.h"
//#include "qmap.h"
//#include "cotautomate_debug.h"

//IState* CStateFactory::build(const QVariantMap &mapState, QObject *parent){

//   IState* state = Q_NULLPTR;
////    const QString type = mapState[QStringLiteral("name")].toString();
////    if(type == QStringLiteral("state_in_maintenance")){
////        state = new CStateMaintenance(mapState,parent);
////    }
////    else if(type == QStringLiteral("state_stoped")){
////        state = new CStateStopped(mapState,parent);
////    }
////    else if(type == QStringLiteral("state_cycle_runnning")){
////        state = new CStateCycleRunning(mapState,parent);
////    }
////    else if(type == QStringLiteral("state_cycle_paused")){
////        state = new CStateCyclePaused(mapState,parent);
////    }
////    else if(type == QStringLiteral("state_blank_cycle_running")){
////        state = new CStateBlankCycleRunning(mapState,parent);
////    }
////    else{
////        state = new CStateUnknow(mapState,parent);
////        qCDebug(COTAUTOMATE_LOG) << "Classe state INCONNUE :" << type;
////    }

//   return state;
//}
