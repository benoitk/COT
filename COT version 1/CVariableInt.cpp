#include "CVariableInt.h"

CVariableInt::CVariableInt(QObject *parent):IVariable(parent)
{
	
}
CVariableInt::CVariableInt(int arg_int):IVariable()
{
	m_iValeur = arg_int;
}

CVariableInt::~CVariableInt()
{

}
QString CVariableInt::toString()const{
	return QString::number(m_iValeur);
}
int CVariableInt::toInt()const{
	return m_iValeur;
}
float CVariableInt::toFloat()const{
	return m_iValeur;
}

void CVariableInt::setValue(int iValue){
	m_iValeur = iValue;
}
void CVariableInt::setValue(QVariant value){
	m_iValeur = value.toInt();
}
QString CVariableInt::getLabel()const{
	return m_label;
}
void CVariableInt::setLabel(QString label){
	m_label = label;
}