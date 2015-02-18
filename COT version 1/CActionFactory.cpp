#include "CActionFactory.h"
#include "CActionCmdPompe.h"
#include "CActionCmdRelay.h"
#include "CActionCmdReadInput.h"
#include "CActionUnknow.h"

#include "qvariant.h"
#include "qmap.h"
#include "qdebug.h"


IAction* CActionFactory::build(QVariantMap mapAction){
	
	IAction* action = NULL;
	if(mapAction["class"].toString() == "cmd_pump"){
		action = new CActionCmdPompe(mapAction);
	}
	else if(mapAction["class"].toString() == "cmd_relay"){
		action = new CActionCmdRelay(mapAction);
	}
	else if(mapAction["class"].toString() == "cmd_read_input"){
		action = new CActionCmdReadInput(mapAction);
	}
	else{
		action = new CActionUnknow(mapAction);
		qDebug() << "Classe action INCONNUE :  " << mapAction["class"].toString();
	
	}

	return action;
}