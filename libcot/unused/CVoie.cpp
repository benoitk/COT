#include "CVoie.h"



CVoie::CVoie(QObject *parent):IVariable(parent)
{
}
CVoie::CVoie(QObject * parent, int iNumVoie):IVariable(parent){
    m_iNumVoie = iNumVoie;
}

CVoie::~CVoie()
{
}


QString CVoie::toString()const{
    return QString::number(m_iNumVoie);
}
int CVoie::toInt()const{
    return m_iNumVoie;
}
float CVoie::toFloat()const{
    return m_iNumVoie;
}

QString CVoie::getLabel()const{
    return m_label;
}
void CVoie::setLabel(QString label){
    m_label = label;
}

