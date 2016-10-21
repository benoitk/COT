#include "CCycleFactory.h"
#include "CCycleAutonome.h"
#include "CCycleMesure.h"
#include "CCyclePause.h"
#include "CCycleMaintenance.h"

#include "cotautomate_debug.h"
#include "qvariant.h"

ICycle* CCycleFactory::build(const QVariantMap &mapCycle, CScheduler* parent){
    //qCDebug(COTAUTOMATE_LOG) << "CCycleFactory::build mapCycle:"<< mapCycle;
    ICycle* cycle = NULL;
    if(mapCycle[QStringLiteral("type")].toString() == QStringLiteral("measure")){
        cycle = new CCycleMesure(mapCycle, parent);
    }else if(mapCycle[QStringLiteral("type")].toString() == QStringLiteral("pause")){
        cycle = new CCyclePause(mapCycle, parent);
    }else if(mapCycle[QStringLiteral("type")].toString() == QStringLiteral("autonome")){
        cycle = new CCycleAutonome(mapCycle, parent);
    }else if(mapCycle[QStringLiteral("type")].toString() == QStringLiteral("maintenance")){
        cycle = new CCycleMaintenance(mapCycle, parent);
    }else{
        qCDebug(COTAUTOMATE_LOG) << "Type cycle INCONNU " << mapCycle[QStringLiteral("type")].toString();
    }
    return cycle;
}

ICycle *CCycleFactory::build(enumTypeCycle type)
{
    ICycle *cycle = Q_NULLPTR;

    switch (type) {
        case e_cycle_measure:
            cycle = new CCycleMesure;
            break;

        case e_cycle_autonome:
            cycle = new CCycleAutonome;
            break;

        case e_cycle_maintenance:
            cycle = new CCycleMaintenance;
            break;

        case e_cycle_pause:
            cycle = new CCyclePause;
            break;

        case e_cycle_all:
        case e_cycle_invalid:
            Q_ASSERT(false);
            break;
    }

    return cycle;
}
