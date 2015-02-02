#include "IAction.h"
#include "CActionCmdPompe.h"
#include "CActionCmdRelay.h"

#include "qvariant.h"
#include "qmap.h"

IAction::IAction(QObject *parent): QObject(parent){}
IAction::IAction(): QObject(){}
IAction::~IAction(){}

IAction* IAction::factory(QVariantMap mapAction){
	IAction* action = NULL;
	if(mapAction["class"].toString() == "cmd_pump"){
		action = new CActionCmdPompe(mapAction);
	}
	if(mapAction["class"].toString() == "cmd_relay"){
		action = new CActionCmdRelay(mapAction);
	}
	return action;
}

