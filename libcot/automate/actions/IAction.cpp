#include "IAction.h"
#include "cotautomate_debug.h"
#include "qvariant.h"


IAction::IAction(const QVariantMap &mapAction, QObject *parent):QObject(parent), m_abort(false){
    m_label = mapAction[tr("fr_FR")].toString();
    if(m_label == "" ) m_label = tr("Label non renseignée");
    m_name = mapAction[QStringLiteral("name")].toString();
    if(m_name == "") m_name =  tr("Nom non renseignée");
}

IAction::~IAction(){}

bool IAction::waitUnitlFinished(){
  return false;
}
bool IAction::finishedWithCriticalError(){
    return false;
}

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

    case actionType::type_cmd_digital_output:
        return tr("Relay command");

    case actionType::type_test:
        return tr("Test");

    }
    return QStringLiteral("**unhandled action type**");
}
QString IAction::getName()const{
    QMutexLocker lock(&m_mutex);
    return m_name;
}
QString IAction::getLabel()const{
    QMutexLocker lock(&m_mutex);
    return m_label;
}
void IAction::setLabel(const QString& lbl){
    m_label = lbl;
}

bool IAction::runAction(){
   m_abort = false;
   qCDebug(COTAUTOMATE_LOG)<< "Action  "
           << " label fr " << m_label
        ;
    return true;
}

void IAction::abortAction(){
    m_abort = true;
}
