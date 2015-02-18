#include "CVariableString.h"

CVariableString::CVariableString(QObject *parent)
	: IVariable(parent)
{

}
CVariableString::CVariableString(QString arg_value)
	: IVariable()
{
	m_sValeur = arg_value;
}
CVariableString::~CVariableString()
{

}

QString CVariableString::toString()const{
	return m_sValeur;
}
int CVariableString::toInt()const{
	return m_sValeur.toInt();
}
float CVariableString::toFloat()const{
	return m_sValeur.toFloat();
}
void CVariableString::setValue(QVariant value){
	m_sValeur = value.toString();
}
void CVariableString::setValue(QString value){
	m_sValeur = value;
}
QString CVariableString::getLabel()const{
	return m_label;
}
void CVariableString::setLabel(QString lbl){
	m_label = lbl;
}