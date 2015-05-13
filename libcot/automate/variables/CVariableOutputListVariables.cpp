#include "CVariableOutputListVariables.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"

CVariableOutputListVariables::CVariableOutputListVariables(QObject *parent)
    : IVariable(parent), m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableOutputListVariables::~CVariableOutputListVariables()
{

}

CVariableOutputListVariables::CVariableOutputListVariables(const QMap<QString, QVariant> &mapVar)
    : IVariable()
    , m_modelExtensionCard(Q_NULLPTR)
{

}
QString CVariableOutputListVariables::getName()const{
    return m_name;
}
void CVariableOutputListVariables::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
}
CModelExtensionCard* CVariableOutputListVariables::getExtensionCard()const{
    return m_modelExtensionCard;
}
IComObserver* CVariableOutputListVariables::getComObserver()const{
    return m_modelExtensionCard;
}
QString CVariableOutputListVariables::getOrganneName()const{
    return m_organneName;
}
QString CVariableOutputListVariables::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableOutputListVariables::setOrganne(CModelExtensionCard* arg_model, const QString &arg_organneName){
    m_modelExtensionCard = arg_model;
    m_organneName = arg_organneName;
}

void CVariableOutputListVariables::writeValue(){
    

}
QString CVariableOutputListVariables::toString(){
    return QStringLiteral(""); //TO DO : do some toString useful
}
int CVariableOutputListVariables::toInt(){
    return 0;
}
float CVariableOutputListVariables::toFloat(){
    return 0;
}
void CVariableOutputListVariables::setValue(const QVariant & value){
    setValue(value.toFloat());
}
void CVariableOutputListVariables::setValue(float value){
    //si vrai envoie la commande (la logique incombe au tech)
    if(value)
        this->writeValue();

    if(!m_listBinds.isEmpty()){
        IVariable* var;
        foreach(var,  m_listBinds){
            var->setValue(QVariant(value));
        }
    }

    emit signalVariableChanged();
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableOutputListVariables::setToBindedValue(const QVariant & value){
    //si vrai envoie la commande (la logique incombe au tech)
    if(value.toBool())
        this->writeValue();
}
QString CVariableOutputListVariables::getLabel()const{
    return m_label;
}
void CVariableOutputListVariables::setLabel(const QString & lbl){
    m_label = lbl;
    emit signalVariableChanged();
}
void CVariableOutputListVariables::addBind(IVariable* arg_var){
    if(arg_var)
        m_listBinds.append(arg_var);
}
variableType CVariableOutputListVariables::getType()const{
    return type_list_variables;
}
IVariable* CVariableOutputListVariables::getIVariable(){
    return this;
}
bool CVariableOutputListVariables::toBool(){
    return false;
}
void CVariableOutputListVariables::switchToUnit(CUnit* targetUnit){
}
void  CVariableOutputListVariables::delBind(IVariable*){

}
CUnit * CVariableOutputListVariables::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableOutputListVariables::isStreamRelated()const{
    return false;
}
QString  CVariableOutputListVariables::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableOutputListVariables::isMeasureRelated()const{
    return false;
}
QString  CVariableOutputListVariables::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableOutputListVariables::isDisplay()const{
    return false;
}
QList<IVariable*>  CVariableOutputListVariables::getListOutBinds()const{
    return m_listBinds;
}
QList<IVariable*>  CVariableOutputListVariables::getListInBinds()const{
    return m_listBinds;

}

void CVariableOutputListVariables::setListOutBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}

void CVariableOutputListVariables::setListInBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}
QVariantMap CVariableOutputListVariables::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_integer"));
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
variableAccess CVariableOutputListVariables::getAccess()const{
    return m_access;
}
int CVariableOutputListVariables::getAddress()const{
    return m_address;
}

void CVariableOutputListVariables::setRelatedStreamName(const QString &variableName)
{

}
