#include "CVariableStream.h"
#include "CUnit.h"
#include "IVariable.h"
#include "ICycle.h"
#include "CAutomate.h"
#include "CVariableFactory.h"

#include "qlinkedlist.h"
CVariableStream::CVariableStream(QObject *parent)
    : IVariable(parent)
{
}
CVariableStream::CVariableStream(const QMap<QString, QVariant> &mapVar)
    : IVariable()
{
    if(mapVar.contains(QStringLiteral("name")))
        m_name = mapVar.value(QStringLiteral("name")).toString();
    else m_name = QStringLiteral("Stream unamed");

    if(mapVar.contains(tr("fr_FR")))
        m_label = mapVar.value(tr("fr_FR")).toString();
    else m_label = QStringLiteral("Stream no label");

    m_activeState = CAutomate::getInstance()->getVariable(mapVar.value(QStringLiteral("active_state")).toString());

    if(mapVar.contains(QStringLiteral("variables"))){
        QVariantList listVariable = mapVar.value(QStringLiteral("variables")).toList();
        foreach(const QVariant &variant, listVariable){
            m_listVariables.append(CAutomate::getInstance()->getVariable(variant.toString()));
        }
    }

    if(mapVar.contains(QStringLiteral("cycles"))){
        QVariantList listVariable = mapVar.value(QStringLiteral("cycles")).toList();
        foreach(const QVariant &variant, listVariable){
            ICycle *cycle = CAutomate::getInstance()->getCycle(variant.toString(), e_cycle_measure);

            // SERES_TODO: avoid null cycles in list.
            if (cycle) {
                cycle->setRelatedStreamName(getName());
            }

            m_listCycles.append(cycle);
        }
    }

    if(mapVar.contains(QStringLiteral("measures"))){
        QVariantList listVariable = mapVar.value(QStringLiteral("measures")).toList();
        foreach(QVariant variant, listVariable){
            QVariantMap map = variant.toMap();
            map.insert(QStringLiteral("type"), QStringLiteral("measure"));
            IVariable* var = CVariableFactory::build(map);
            m_listMeasures.append(var);
        }
    }


}

CVariableStream::~CVariableStream()
{
}
QList<IVariable*> CVariableStream::getListVariables()
{
    return m_listVariables;
}
//QList<CVariableMeasure*> CVariableStream::getListMeasures(){
QList<IVariable*> CVariableStream::getListMeasures(){
    //TO DO à changer en liste de mesure
    return m_listMeasures;
}
QList<ICycle*> CVariableStream::getListCycles(){
    return m_listCycles;
}
IVariable* CVariableStream::getActiveState(){
    return m_activeState;
}

bool CVariableStream::removeVariable(IVariable *var)
{
    const bool result = m_listVariables.removeOne(var);

    if (result) {
        emit signalVariableChanged(this);
    }

    return result;
}
bool CVariableStream::addVariable(IVariable *var){
    bool result = !m_listVariables.contains(var);

    if (result) {
        m_listVariables.append(var);
        emit signalVariableChanged(this);
    }

    return result;
}

void CVariableStream::removeCycle(const QString &name)
{
    for (int i = 0; i < m_listCycles.count(); ++i) {
        ICycle *cycle = m_listCycles[i];

        if (!cycle) {
            // KDAB_TODO: Uncomment when using final api
            //Q_ASSERT(false);
            continue;
        }

        if (cycle->getName() == name) {
            cycle->setRelatedStreamName(QString());
            m_listCycles.removeAt(i);
            // SERES_TODO - should inform automat about change ?
            break;
        }
    }

    emit signalVariableChanged(this);
}

void CVariableStream::addMeasure(IVariablePtr var)
{
    // SERES_TODO propagate change to the automate so the right signal is emitted
    if (!m_listMeasures.contains(var)) {
        m_listMeasures << var;
    }

    emit signalVariableChanged(this);
}

void CVariableStream::removeMeasure(IVariablePtr var)
{
    // SERES_TODO propagate change to the automate so the right signal is emitted
    if (m_listMeasures.contains(var)) {
        m_listMeasures.removeAll(var);
    }

    emit signalVariableChanged(this);
}

QString CVariableStream::toString(){
    return m_label;
}
int CVariableStream::toInt(){
    return 0;
}
float CVariableStream::toFloat(){
    return 0;
}
bool CVariableStream::toBool(){
    return false;
}
QVariant CVariableStream::toVariant(){
    return QVariant(m_label);
}

void CVariableStream::setValue(int iValue){
}
void CVariableStream::setValue(const QVariant & value){
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableStream::setToBindedValue(const QVariant & value){

}
enumVariableType CVariableStream::getType()const{
    return e_type_stream;
}
void CVariableStream::switchToUnit(CUnit* targetUnit){

}

//TO DO : change name to CVariableStream()
QVariantMap CVariableStream::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("stream"));
    QList<QVariant> listVars;
    foreach(IVariable* var, m_listVariables){
        listVars.append(var->getName());
    }
    mapSerialise.insert(QStringLiteral("variables"), listVars);
    QList<QVariant> listMeasures;
    foreach(IVariable* var, m_listMeasures){
        listMeasures.append(var->serialize());
    }
    mapSerialise.insert(QStringLiteral("measures"), listMeasures);
    QList<QVariant> listCycles;
    foreach(IVariable* cycle, m_listMeasures){
        listCycles.append(cycle->getName());
    }
    mapSerialise.insert(QStringLiteral("measures"), listMeasures);
    return mapSerialise;
}

void CVariableStream::addCycle(ICycle *cycle)
{
    if (!m_listCycles.contains(cycle)) {
        cycle->setRelatedStreamName(getName());
        m_listCycles << cycle;
    }

    emit signalVariableChanged(this);
}
