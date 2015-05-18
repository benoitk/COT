#include "CVariableUnknow.h"
#include "CUnit.h"
#include "qlinkedlist.h"
CVariableUnknow::CVariableUnknow()
    : IVariable()
{

}

CVariableUnknow::~CVariableUnknow()
{

}

QString CVariableUnknow::getName()const{
    return QStringLiteral("unknow var");
}
void CVariableUnknow::setName(const QString& name){
}
QString CVariableUnknow::toString(){
    return tr("Variable inconnu");
}
int CVariableUnknow::toInt(){
    return 0;
}
float CVariableUnknow::toFloat(){
    return 0;
}
bool CVariableUnknow::toBool(){
    return false;
}
void CVariableUnknow::setValue(const QVariant &){
}
QString CVariableUnknow::getLabel()const{
    return tr("Variable inconnu");
}
void CVariableUnknow::setLabel(const QString &){
}
void CVariableUnknow::addBind(IVariable* arg_var){
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableUnknow::setToBindedValue(const QVariant & value){
}
variableType CVariableUnknow::getType()const{
    return type_unknow;
}
void CVariableUnknow::switchToUnit(CUnit* targetUnit){

}
void  CVariableUnknow::delBind(IVariable*){

}
CUnit * CVariableUnknow::getUnit() const {
    return Q_NULLPTR;
}
bool  CVariableUnknow::isStreamRelated()const{
    return false;
}
QString  CVariableUnknow::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableUnknow::isMeasureRelated()const{
    return false;
}
QString  CVariableUnknow::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableUnknow::isDisplay()const{
    return false;
}
QList<IVariable*>  CVariableUnknow::getListOutBinds()const{
    QList<IVariable*> list;
    return list;
}
QList<IVariable*>  CVariableUnknow::getListInBinds()const{
    QList<IVariable*> list;
    return list;

}

void CVariableUnknow::setListOutBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}

void CVariableUnknow::setListInBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}
QVariantMap CVariableUnknow::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("unserialized"), QStringLiteral("CVariableUnknow"));
    return mapSerialise;
}
variableAccess CVariableUnknow::getAccess()const{
    return access_read;
}
int CVariableUnknow::getAddress()const{
    return 0;
}

void CVariableUnknow::setRelatedStreamName(const QString &variableName)
{

}

void CVariableUnknow::setAccess(variableAccess access)
{
    Q_UNUSED(access);
}
