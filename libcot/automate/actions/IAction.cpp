#include "IAction.h"
#include "ICycle.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"
#include "qvariant.h"


IAction::IAction(const QVariantMap &mapAction, CAutomate *parent):QObject(parent), m_abort(false), m_automate(parent){
    m_label = mapAction[tr("en_US")].toString();
    if(m_label == "" ) m_label = tr("None given label");
    m_name = mapAction[QStringLiteral("name")].toString();
    if(m_name == "") m_name =  tr("None given name");

}

IAction::~IAction(){}

bool IAction::waitUntilFinished(){
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

    case type_acquisition_cit_npoc:
        return tr("CIT/NPOC measure acquisition");

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

bool IAction::runAction(ICycle* arg_stepParent){
   QMutexLocker lock(&m_mutex);
   m_stepParent = arg_stepParent;
    m_abort = false;
   qCDebug(COTAUTOMATE_LOG)<< "Action  "
           << " label fr " << m_label
        ;
    return true;
}

void IAction::abortAction(){
    m_abort = true;
}


ICycle* IAction::getStepParent(){
    QMutexLocker lock(&m_mutex);
    ICycle* cycle = m_stepParent;
    return cycle;
}

void IAction::updateActionInfos(QString arg_actionInfo, ICycle* arg_stepParent){
    arg_stepParent->updateCycleInfosAction(arg_actionInfo);
}

QVariantMap IAction::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("en_US"), m_label);
    return mapSerialise;
}
