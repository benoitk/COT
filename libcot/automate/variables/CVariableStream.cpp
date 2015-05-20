#include "CVariableStream.h"
#include "CUnit.h"
#include "IVariable.h"
#include "ICycle.h"
#include "CAutomate.h"
#include "CVariableFactory.h"

#include "qlinkedlist.h"
CVariableStream::CVariableStream(QObject *parent)
    : IVariable(parent)
    , m_access(access_read_write)
{
}
CVariableStream::CVariableStream(const QMap<QString, QVariant> &mapVar)
    : IVariable()
    , m_access(access_read_write)
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
            ICycle *cycle = CAutomate::getInstance()->getCycle(variant.toString(), CYCLE_MESURE);

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
QList<IVariable*> CVariableStream::getListMeasures(){
    return m_listMeasures;
}
QList<ICycle*> CVariableStream::getListCycles(){
    return m_listCycles;
}
IVariable* CVariableStream::getActiveState(){
    return m_activeState;
}

void CVariableStream::delVariable(IVariable *var)
{
    m_listVariables.removeOne(var);
}

void CVariableStream::delCycle(const QString &name)
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
            // Customer - should inform automat about change ?
            break;
        }
    }
}

void CVariableStream::setRelatedStreamName(const QString &variableName)
{

}
void CVariableStream::setAccess(variableAccess access)
{
    m_access = access;
}
QString CVariableStream::getName()const{
    return m_name;
}
void CVariableStream::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
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
QString CVariableStream::getLabel()const{
    return m_label;
}
void CVariableStream::setLabel(const QString & label){
    m_label = label;
    emit signalVariableChanged();
}

void CVariableStream::setValue(int iValue){
}
void CVariableStream::setValue(const QVariant & value){
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableStream::setToBindedValue(const QVariant & value){

}
variableType CVariableStream::getType()const{
    return type_stream;
}
void CVariableStream::switchToUnit(CUnit* targetUnit){

}
void  CVariableStream::delBind(IVariable*){

}
void  CVariableStream::addBind(IVariable*){

}
CUnit * CVariableStream::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableStream::isStreamRelated()const{
    return false;
}
QString  CVariableStream::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableStream::isMeasureRelated()const{
    return false;
}
QString  CVariableStream::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableStream::isDisplay()const{
    return false;
}
QList<IVariable*>  CVariableStream::getListOutBinds()const{
    QList<IVariable*> list;
    return list;
}
QList<IVariable*>  CVariableStream::getListInBinds()const{
    QList<IVariable*> list;
    return list;

}
//TO DO : change name to CVariableStream()
QVariantMap CVariableStream::serialise(){
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
        listMeasures.append(var->serialise());
    }
    mapSerialise.insert(QStringLiteral("measures"), listMeasures);
    QList<QVariant> listCycles;
    foreach(IVariable* cycle, m_listMeasures){
        listCycles.append(cycle->getName());
    }
    mapSerialise.insert(QStringLiteral("measures"), listMeasures);
    return mapSerialise;
}

void CVariableStream::setListOutBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}

void CVariableStream::setListInBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}
variableAccess CVariableStream::getAccess()const{
    return m_access;
}
int CVariableStream::getAddress()const{
    return m_address;
}

void CVariableStream::addCycle(ICycle *cycle)
{
    if (!m_listCycles.contains(cycle)) {
        cycle->setRelatedStreamName(getName());
        m_listCycles << cycle;
    }
}
