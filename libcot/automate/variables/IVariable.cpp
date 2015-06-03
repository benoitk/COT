#include "IVariable.h"
#include "qdebug.h"
int IVariable::FLOAT_PRECISION = 3;

IVariable::IVariable(QObject *parent)
    : QObject(parent)
    , m_access(access_read)
    , m_address(0)
{
    m_label = "label_IVariable";
    m_name = "name_IVariable";
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
        case VariableOrganTypeNone:
            return tr("None");

        case VariableOrganTypeInput:
            return tr("Input");

        case VariableOrganTypeOutput:
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
    qDebug() << m_label << "  " << getType() << getName();
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
    return Q_NULLPTR;
}
bool  IVariable::isStreamRelated()const{
    return false;
}
QString  IVariable::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  IVariable::isMeasureRelated()const{
    return false;
}
QString  IVariable::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
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
    return VariableOrganTypeNone;
}
IVariable* IVariable::getIVariable(){
    return this;
}
