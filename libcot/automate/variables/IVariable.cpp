#include "IVariable.h"
#include "CVariableMeasure.h"
#include "CVariableStream.h"
#include "CAutomate.h"
#include "CUnit.h"
#include "ICom.h"

#include "qdebug.h"
int IVariable::FLOAT_PRECISION = 3;

IVariable::IVariable(CAutomate* arg_automate, QObject *parent)
    : QObject(parent)
    , m_access(e_access_read)
    , m_address(0)
    , m_automate(arg_automate)
{
    m_label = "label_IVariable";
    m_name = "name_IVariable";
    m_unit = new CUnit("no_unit", "");
}
IVariable::IVariable(const QVariantMap& arg_varMap, CAutomate* arg_automate, QObject* parent):
    QObject(parent),
    m_automate(arg_automate)
{
    QString sAccess = arg_varMap.value(QStringLiteral("access")).toString();

    if(sAccess == QStringLiteral("read_write")) m_access = e_access_read_write;
    else if(sAccess == QStringLiteral("write")) m_access = e_access_write;
    else /*if(sAccess == QStringLiteral("write"))*/ m_access = e_access_read;


     m_name = arg_varMap.value(QStringLiteral("name")).toString();
     m_label = arg_varMap.value(tr("en_US")).toString();

     if(arg_varMap.contains(QStringLiteral("address"))) m_address = arg_varMap.value(QStringLiteral("address")).toInt();

    m_unit = m_automate->getUnit(arg_varMap.value(QStringLiteral("unit")).toString());

    QStringList listComName = arg_varMap.value(QStringLiteral("coms_name_used")).toStringList();
    foreach(QString comName, listComName){
        m_coms.append(m_automate->getCom(comName));
    }
//    m_unit = new CUnit("tmp", "µg/l");
}


void IVariable::initComs(){
    foreach(ICom* com, m_coms){
        com->addVariableOnDataTable(this);
    }
}

//IVariable::IVariable(): QObject()
//, m_access(e_access_read)
//, m_address(0){
//    m_label = "label_IVariable";
//    m_name = "name_IVariable";
//     m_unit = new CUnit("no_unit", "");
//}

CAutomate* IVariable::getAutomate(){
    return m_automate;
}

QString IVariable::typeToString(enumVariableType type)
{
    switch (type) {
        case e_type_bool:
            return tr("Boolean");

        case e_type_float:
            return tr("Float");

        case e_type_int:
            return tr("Integer");

        case e_type_string:
            return tr("String");

        case e_type_stream:
            return tr("Stream");

        case e_type_measure:
            return tr("Measure");

        case e_type_list_variables:
            return tr("Variables list");

        case type_mutable:
            return tr("Mutable");

        case e_type_unknow:
            return tr("Unknown");
    }

    return QStringLiteral("**unhandled variable type**");
}

QString IVariable::organTypeToString(enumVariableOrganType type)
{
    switch (type) {
        case e_type_organ_none:
            return tr("None");

        case e_type_organ_input:
            return tr("Input");

        case e_type_organ_output:
            return tr("Output");
    }

    return QStringLiteral("**unhandled organ type**");
}



QString IVariable::getName()const{
    return m_name;
}
void IVariable::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged(this);
}



QString IVariable::getLabel()const{
    return m_label;
}
void IVariable::setLabel(const QString & lbl){
    m_label = lbl;
    emit signalVariableChanged(this);
}

void IVariable::addBind(IVariable* arg_var){
    if(arg_var)
        m_listBinds.append(arg_var);
}




void  IVariable::delBind(IVariable* arg_var){
    m_listBinds.removeAll(arg_var);
}
CUnit * IVariable::getUnit() const{
//    return Q_NULLPTR;
    return m_unit;
}
bool  IVariable::isStreamRelated()const{
    foreach(CVariableStream* stream, m_automate->getListStreams()){
        foreach(IVariable* var, stream->getListVariables()){
            if(var == this) return true;
        }
    }

    return false;
}
QString  IVariable::getRelatedStreamName()const{
    foreach(CVariableStream* stream, m_automate->getListStreams()){
        foreach(IVariable* var, stream->getListVariables()){
            if(var == this) return stream->getName();
        }
    }

    return tr("Not related to a stream");
}
bool  IVariable::isMeasureRelated()const{
    foreach(CVariableStream* stream, m_automate->getListStreams()){
        foreach(IVariable* measure,  stream->getListMeasures()){
            foreach(IVariable* var, ((CVariableMeasure*)measure)->getListVariables()){
                if(var == this) return true;
            }
        }
    }
    return false;
}
QString  IVariable::getRelatedMeasureName()const{
    CVariableMeasure *var = getRelatedMeasure();
    if (var)
        return var->getName();
    else
        return tr("Not related to a measure");
}
CVariableMeasure *IVariable::getRelatedMeasure() const
{
    foreach (CVariableStream* stream, m_automate->getListStreams()) {
        foreach (IVariable* measure, stream->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure*>(measure);
            if (measureVar->getMeasureVariable() == this)
                return measureVar;
        }
    }
    return Q_NULLPTR;
}
bool  IVariable::isDisplay()const{
    return false;
}
void IVariable::checkBindedVariable(QVariant arg_variant){
    if(!m_listBinds.isEmpty()){
        IVariable* var;
        foreach(var,  m_listBinds){
            if(var->getUnit() != m_unit && var->getUnit()) {
                arg_variant.setValue(m_unit->convert(var->getUnit()->getName(), arg_variant));
            }
            var->setToBindedValue(arg_variant);
        }
    }
}

QList<IVariable*>  IVariable::getListOutBinds()const{
    return m_listBinds;
}
QList<IVariable*>  IVariable::getListInBinds()const{
    QList<IVariable*>  list;
    foreach (IVariable* var, m_automate->getMapVariables()) {
        foreach(IVariable* varFromBinds, var->getListOutBinds()){
            if(varFromBinds == this) {
                list.append(var);
                break;
            }
        }
    }
    return list;
}

void IVariable::setListOutBinds(const QList<IVariable *> & arg_list)
{
    m_listBinds = arg_list;
}

void IVariable::setListInBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}


enumVariableAccess IVariable::getAccess()const{
    return m_access;
}
int IVariable::getAddress()const{
    return m_address;
}

void IVariable::setRelatedStreamName(const QString &variableName)
{

}

void IVariable::setAccess(enumVariableAccess access)
{
    m_access = access;
}

void IVariable::setAddress(int address)
{
    m_address = address;
}
enumVariableOrganType IVariable::getOrganType() const {
    return e_type_organ_none;
}
IVariable* IVariable::getIVariable(){
    return this;
}

QVariantMap IVariable::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("en_US"), m_label);
    switch(m_access){
    case e_access_read:
        mapSerialise.insert(QStringLiteral("access"), QStringLiteral("read"));
        break;
    case e_access_write:
        mapSerialise.insert(QStringLiteral("access"), QStringLiteral("write"));
        break;
    case e_access_read_write:
    default:
        mapSerialise.insert(QStringLiteral("access"), QStringLiteral("read_write"));
        break;
    }
    mapSerialise.insert(QStringLiteral("unit"), m_unit->getName());

    QStringList listComName;
    foreach(ICom* com, m_coms){
        listComName.append(com->getName());
    }
    mapSerialise.insert(QStringLiteral("coms_name_used"), listComName);

    return mapSerialise;
}
bool IVariable::operator<(IVariable* arg_var){
    return this->toFloat() < arg_var->toFloat();
}

bool IVariable::operator>(IVariable* arg_var){
    return this->toFloat() > arg_var->toFloat();
}
