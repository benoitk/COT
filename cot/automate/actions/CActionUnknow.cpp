#include "CActionUnknow.h"

#include "qdebug.h"
CActionUnknow::CActionUnknow(QObject *parent)
	: IAction(parent)
{

}
CActionUnknow::CActionUnknow(QVariantMap mapAction)
	: IAction()
{
	m_label = mapAction[tr("FR_lbl")].toString();
	m_name = mapAction["name"].toString();
	 

}
CActionUnknow::~CActionUnknow()
{

}

bool CActionUnknow::runAction(){
	qDebug() <<  "Action inconnu " ;
	return true;
}

QString CActionUnknow::getName()const{
	return m_name; 
}