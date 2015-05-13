#include "cint.h"

CInt::CInt(QObject *parent):IVariable(parent)
{
    
}

CInt::~CInt()
{

}
QString CInt::toString()const{
    return QString::number(m_iValeur);
}
int CInt::toInt()const{
    return m_iValeur;
}
float CInt::toFloat()const{
    return m_iValeur;
}

void CInt::setValeur(int iValeur){
    m_iValeur = iValeur;
}
QString CInt::getLabel()const{
    return m_label;
}
void CInt::setLabel(QString label){
    m_label = label;
}