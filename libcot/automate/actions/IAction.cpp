#include "IAction.h"

#include "qvariant.h"


IAction::IAction(const QVariantMap &mapAction){
    m_label = mapAction[tr("FR_lbl")].toString();
    m_name = mapAction[QStringLiteral("name")].toString();
}
IAction::IAction(): QObject(){
    m_label = tr("Label non renseignée");
    m_name =  tr("Nom non renseignée");
}
IAction::IAction(QObject *parent): QObject(parent){}

IAction::~IAction(){}

/*IAction* IAction::factory(QVariantMap mapAction){
    IAction* action = NULL;
    if(mapAction["class"].toString() == "cmd_pump"){
        action = new CActionCmdPompe(mapAction);
        action->factory(mapAction);
    }
    if(mapAction["class"].toString() == "cmd_relay"){
        action = new CActionCmdRelay(mapAction);
    }
    return action;
}*/

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
