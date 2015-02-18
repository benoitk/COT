#include "CVariableFloat.h"

CVariableFloat::CVariableFloat(QObject *parent)
	: IVariable(parent)
{

}
CVariableFloat::CVariableFloat(float arg_value)
	: IVariable()
{
	m_fValeur = arg_value;
}
CVariableFloat::~CVariableFloat()
{

}


QString CVariableFloat::toString()const{
	return QString::number(m_fValeur);
}
int CVariableFloat::toInt()const{
	return m_fValeur;
}
float CVariableFloat::toFloat()const{
	return m_fValeur;
}
void CVariableFloat::setValue(QVariant value){
	setValue(value.toFloat());
}
void CVariableFloat::setValue(float value){
	m_fValeur = value;
}
QString CVariableFloat::getLabel()const{
	return m_label;
}
void CVariableFloat::setLabel(QString lbl){
	m_label = lbl;
}