#include "IState.h"

#include "IVariable.h"
#include "CAutomate.h"

#include <QVariant>

IState::IState(const QVariantMap &mapState, QObject *parent) : QObject(parent)
{
    m_label = mapState.value(tr("en_US")).toString();
    if(m_label == "" ) m_label = tr("None given label");
    m_name = mapState.value(QStringLiteral("name")).toString();
    if(m_name == "") m_name =  tr("None given name");

    CAutomate* automate = CAutomate::getInstance();
    QVariantList listState = mapState.value("output_variables").toList();
    foreach(QVariant variant, listState) {
        IVariable* outputVar = automate->getVariable(variant.toString());
        switch(outputVar->getType()){
        case e_type_unknow : break;
        default :
            m_listVariablesToSet.append(outputVar);
            break;
        }

    }

}

void IState::setStateVariables(bool arg_State){
    foreach (IVariable* var, m_listVariablesToSet) {
        var->setValue(arg_State);
    }
}

QString IState::getName(){
    return m_name;
}

enumStateType IState::getType(){
    return m_type;
}


QVariantMap IState::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("en_US"), m_label);


    return mapSerialise;
}
