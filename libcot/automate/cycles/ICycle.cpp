#include "ICycle.h"
//#include "qvariant.h"
//#include "qmap.h"
//
//
//#include "CCycleAutonome.h"
//#include "CCycleIO.h"
//#include "CCycleMaintenance.h"
//#include "CCycleMesure.h"
//#include "CCyclePause.h"
//
//#include "cotautomate_debug.h"

ICycle::ICycle(QObject *parent)
    : QObject(parent)
{

}
ICycle::ICycle()
    : QObject()
{

}

ICycle::~ICycle()
{

}

bool ICycle::isStreamRelated() const
{
    return !getRelatedStreamName().isEmpty();
}

CStep *ICycle::getStep(int index) const
{
    return getListSteps().at(index);
}

QString ICycle::typeToString(eTypeCycle type)
{
    switch (type) {
        case CYCLE_ALL:
            return tr("All");

        case CYCLE_MESURE:
            return tr("Measure");

        case CYCLE_AUTONOME:
            return tr("Autonome");

        case CYCLE_MAINTENANCE:
            return tr("Maintenance");

        case CYCLE_PAUSE:
            return tr("Pause");

        case CYCLE_INVALID:
            return tr("Invalid");
    }

    return QStringLiteral("**unhandled cycle type**");
}

//ICycle* ICycle::factory(QVariantMap mapCycle){
//    qCDebug(COTAUTOMATE_LOG) << "Pas la bonne factory !!!" ;
//    ICycle* cycle = NULL;
//    if(mapCycle["type"].toString() == "measure"){
//        cycle = new CCycleMesure(mapCycle);
//    }else if(mapCycle["type"].toString() == "pause"){
//        cycle = new CCyclePause(mapCycle);
//    }
//    return cycle;
//}
//ICycle* ICycle::factory(QVariantMap mapCycle,QMap<QString, IAction*> mapAction){
//    qCDebug(COTAUTOMATE_LOG) << " ##ICycle::factory " ;
//    ICycle* cycle = NULL;
//    if(mapCycle["type"].toString() == "measure"){
//        cycle = new CCycleMesure(mapCycle, mapAction);
//    }else if(mapCycle["type"].toString() == "pause"){
//        cycle = new CCyclePause(mapCycle);
//    }
//    qCDebug(COTAUTOMATE_LOG) << " ## END ICycle::factory " ;
//    return cycle;
//}
