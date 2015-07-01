#include "IVariable.h"
#include "CVariableMeasure.h"
#include "CVariableStream.h"
#include "CAutomate.h"
#include "CUnit.h"
#include "qdebug.h"
int IVariable::FLOAT_PRECISION = 3;

IVariable::IVariable(QObject *parent)
    : QObject(parent)
    , m_access(access_read)
    , m_address(0)
{
    m_label = "label_IVariable";
    m_name = "name_IVariable";
     m_unit = new CUnit("tmp", "µg/l");
}
IVariable::IVariable(const QVariantMap& arg_varMap): QObject(){
    QString sAccess = arg_varMap.value(QStringLiteral("access")).toString();

    if(sAccess == QStringLiteral("read_write")) m_access = access_read_write;
    else if(sAccess == QStringLiteral("write")) m_access = access_write;
    else /*if(sAccess == QStringLiteral("write"))*/ m_access = access_read;


     m_name = arg_varMap.value(QStringLiteral("name")).toString();
     m_label = arg_varMap.value(tr("fr_FR")).toString();

     if(arg_varMap.contains(QStringLiteral("address"))) m_address = arg_varMap.value(QStringLiteral("address")).toInt();

    m_unit = CAutomate::getInstance()->getUnit(arg_varMap.value(QStringLiteral("unit")).toString());
//    m_unit = new CUnit("tmp", "µg/l");
}

IVariable::IVariable(): QObject()
, m_access(access_read)
, m_address(0){
    m_label = "label_IVariable";
    m_name = "name_IVariable";
     m_unit = new CUnit("tmp", "µg/lkk");
}

QString IVariable::typeToString(variableType type)
{
    switch (type) {
        case type_bool:
            return tr("Boolean");

        case type_float:
            return tr("Float");

        case type_int:
            return tr("Integer");

        case type_string:
            return tr("String");

        case type_stream:
            return tr("Stream");

        case type_measure:
            return tr("Measure");

        case type_list_variables:
            return tr("Variables list");

        case type_mutable:
            return tr("Mutable");

        case type_unknow:
            return tr("Unknown");
    }

    return QStringLiteral("**unhandled variable type**");
}

QString IVariable::organTypeToString(VariableOrganType type)
{
    switch (type) {
        case type_organ_none:
            return tr("None");

        case type_organ_input:
            return tr("Input");

        case type_organ_output:
            return tr("Output");
    }

    return QStringLiteral("**unhandled organ type**");
}



QString IVariable::getName()const{
    return m_name;
}
void IVariable::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
}



QString IVariable::getLabel()const{
    return m_label;
}
void IVariable::setLabel(const QString & lbl){
    m_label = lbl;
    emit signalVariableChanged();
}

void IVariable::addBind(IVariable* arg_var){
    if(arg_var)
        m_listBinds.append(arg_var);
}




void  IVariable::delBind(IVariable*){

}
CUnit * IVariable::getUnit() const{
//    return Q_NULLPTR;
    return m_unit;
}
bool  IVariable::isStreamRelated()const{
    foreach(CVariableStream* stream, CAutomate::getInstance()->getListStreams()){
        foreach(IVariable* var, stream->getListVariables()){
            if(var == this) return true;
        }
    }

    return false;
}
QString  IVariable::getRelatedStreamName()const{
    foreach(CVariableStream* stream, CAutomate::getInstance()->getListStreams()){
        foreach(IVariable* var, stream->getListVariables()){
            if(var == this) return stream->getName();
        }
    }

    return tr("Not related to a stream");
}
bool  IVariable::isMeasureRelated()const{
    foreach(CVariableStream* stream, CAutomate::getInstance()->getListStreams()){
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
    foreach (CVariableStream* stream, CAutomate::getInstance()->getListStreams()) {
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
QList<IVariable*>  IVariable::getListOutBinds()const{
    return m_listBinds;
}
QList<IVariable*>  IVariable::getListInBinds()const{
    return m_listBinds;

}

void IVariable::setListOutBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}

void IVariable::setListInBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}


variableAccess IVariable::getAccess()const{
    return m_access;
}
int IVariable::getAddress()const{
    return m_address;
}

void IVariable::setRelatedStreamName(const QString &variableName)
{

}

void IVariable::setAccess(variableAccess access)
{
    m_access = access;
}

void IVariable::setAddress(int address)
{
    m_address = address;
}
VariableOrganType IVariable::getOrganType() const {
    return type_organ_none;
}
IVariable* IVariable::getIVariable(){
    return this;
}
