#include "CVariableVoie.h"



CVariableVoie::CVariableVoie(QObject *parent):IVariable(parent)
{	
}
CVariableVoie::CVariableVoie(QObject * parent, int iNumVoie):IVariable(parent){
	m_iNumVoie = iNumVoie;	 
}

CVariableVoie::~CVariableVoie()
{
}


QString CVariableVoie::toString()const{
	return QString::number(m_iNumVoie);
}
int CVariableVoie::toInt()const{
	return m_iNumVoie;
}
float CVariableVoie::toFloat()const{
	return m_iNumVoie;
}

QString CVariableVoie::getLabel()const{
	return m_label;
}
void CVariableVoie::setLabel(QString label){
	m_label = label;
}

void CVariableVoie::setValue(int iValue){
	m_iNumVoie = iValue;
}
void CVariableVoie::setValue(QVariant value){
	m_iNumVoie = value.toInt();
}