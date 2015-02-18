#include "CVariableBool.h"

CVariableBool::CVariableBool(QObject *parent)
	: IVariable(parent)
{

}

CVariableBool::CVariableBool(bool arg_value)
	: IVariable()
{
	m_bValeur = arg_value;
}


CVariableBool::~CVariableBool()
{

}

QString CVariableBool::toString()const{
	if(m_bValeur)
		return tr("vrai");
	else
		return tr("faux");
}
int CVariableBool::toInt()const{
	return m_bValeur;
}
float CVariableBool::toFloat()const{
	return m_bValeur;
}
void CVariableBool::setValue(QVariant value){
	m_bValeur = value.toBool();
}
void CVariableBool::setValue(bool value){
	m_bValeur = value;
}
QString CVariableBool::getLabel()const{
	return m_label;
}
void CVariableBool::setLabel(QString lbl){
	m_label = lbl;
}