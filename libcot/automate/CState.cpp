#include "CState.h"

#include "IVariable.h"

#include <QVariant>

CState::CState(QObject *parent) : QObject(parent)
  , m_label(tr("None given label")), m_name(tr("None given name")),m_state(false)
{

}


QString CState::getName(){
    return m_name;
}

void CState::setName(QString arg){
    m_name = arg;
}

QString CState::getlabel(){
    return m_label;
}

void CState::setLabel(QString arg){
    m_label = arg;
}

bool CState::getState(){
    return m_state;
}

void CState::setState(bool arg){
    m_state = arg;
    foreach (IVariable* var, m_listVariablesToSet) {
        var->setValue(arg);
    }
}
void CState::addOutputVariable(IVariable* arg){
    m_listVariablesToSet.append(arg);
}

QVariantMap CState::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(QStringLiteral("default_state"), m_state);
    return mapSerialise;
}
