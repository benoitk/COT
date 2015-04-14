#include "CActionFactory.h"
#include "CActionCmdPompe.h"
#include "CActionCmdRelay.h"
#include "CActionCmdReadInput.h"
#include "CActionUnknow.h"

#include "qvariant.h"
#include "qmap.h"
#include "qdebug.h"


IAction* CActionFactory::build(const QVariantMap &mapAction){
	
	IAction* action = NULL;
    if(mapAction[QStringLiteral("type")].toString() == QStringLiteral("cmd_pump")){
		action = new CActionCmdPompe(mapAction);
	}
    else if(mapAction[QStringLiteral("type")].toString() == QStringLiteral("cmd_relay")){
		action = new CActionCmdRelay(mapAction);
	}
    else if(mapAction[QStringLiteral("type")].toString() == QStringLiteral("cmd_read_input")){
		action = new CActionCmdReadInput(mapAction);
	}
	else{
		action = new CActionUnknow(mapAction);
        qDebug() << "Classe action INCONNUE :  " << mapAction[QStringLiteral("type")].toString();
	
	}

	return action;
}
