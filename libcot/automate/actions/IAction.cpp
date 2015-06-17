#include "IAction.h"

#include "qvariant.h"


IAction::IAction(const QVariantMap &mapAction, QObject *parent):QObject(parent){
    m_label = mapAction[tr("FR_lbl")].toString();
    if(m_label == "" ) m_label = tr("Label non renseignée");
    m_name = mapAction[QStringLiteral("name")].toString();
    if(m_name == "") m_name =  tr("Nom non renseignée");
}

IAction::~IAction(){}


QString IAction::typeToString(actionType arg_type)
{
    switch (arg_type) {
        case actionType::type_action_unknow:
            return tr("Unknow");

        case actionType::type_block:
            return tr("Steps block");

        case actionType::type_cmd_pump:
            return tr("Pump command");

        case actionType::type_cmd_read_input:
            return tr("Read input");

        case actionType::type_cmd_relay:
            return tr("Relay command");


    }
    return QStringLiteral("**unhandled action type**");
}
QString IAction::getName()const{
    return m_name;
}
QString IAction::getLabel()const{
    return m_label;
}
void IAction::setLabel(const QString& lbl){
    m_label = lbl;
}
