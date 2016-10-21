#include "ccommandfactory.h"

#include "ccommandunknow.h"
#include "CCommandPlayStopCycle.h"
#include "CCommandStopEndCycle.h"

#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"



ICommand* CCommandFactory::build(const QVariantMap &mapCommand, CAutomate *parent){

    ICommand* command = Q_NULLPTR;
    const QString type = mapCommand[QStringLiteral("name")].toString();
    if(type == QStringLiteral("cmd_play_stop_cycle")){
        command = new CCommandPlayStopCycle(mapCommand,parent);
    }
     else if(type == QStringLiteral("cmd_stop_end_cycle")){
        command = new CCommandStopEndCycle(mapCommand,parent);
    }
    else{
        command = new CCommandUnknow(mapCommand,parent);
        qCDebug(COTAUTOMATE_LOG) << "Classe command INCONNUE :" << type;
    }

    return command;
}

