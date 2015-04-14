#include "CStep.h"
#include "IAction.h"

#include "qvariant.h"
#include "qmap.h"

CStep::CStep(const QMap<QString, QVariant> &mapStep)
	: QObject()
{
	//builder actions
}

CStep::~CStep()
{

}

QString CStep::getLabel()const{
	return m_label;
}
void CStep::setLabel(const QString &label){
	m_label = label;
}
QList<IAction*> CStep::getListActions()const{
	return m_lisActions;
}
float CStep::getNumStep()const{
	return m_numStep;
}
void CStep::setNumStep(float numStep){
	m_numStep = numStep;
}
CStep* CStep::getNextStep()const{
	return m_nextStep;
}
void CStep::setNextStep(CStep* step){
	m_nextStep = step;
}
