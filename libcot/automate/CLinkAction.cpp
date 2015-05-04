#include "CLinkAction.h"

CLinkAction::CLinkAction(int arg_step, IAction* arg_action)
	: QObject()
{
	m_action = arg_action;
}

CLinkAction::~CLinkAction()
{

}

IAction* CLinkAction::getAction()const
{
	return m_action;
}

