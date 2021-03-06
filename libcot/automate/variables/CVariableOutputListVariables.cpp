﻿#include "CVariableOutputListVariables.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "IOrgan.h"
CVariableOutputListVariables::CVariableOutputListVariables(CAutomate* arg_automate, QObject *parent)
    : IVariable(arg_automate, parent),IVariableOutput()
{

}

CVariableOutputListVariables::~CVariableOutputListVariables()
{

}

CVariableOutputListVariables::CVariableOutputListVariables(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject *parent)
    : IVariable(arg_automate, parent),IVariableOutput()
{

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
QVariant CVariableOutputListVariables::toVariant(){
    return QVariant();
}

void CVariableOutputListVariables::setValue(const QVariant & value){

}

//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableOutputListVariables::setToBindedValue(const QVariant & value){

}
void CVariableOutputListVariables::switchToUnit(CUnit* arg_unit){
    //à faire
}

enumVariableType CVariableOutputListVariables::getType()const{
    return e_type_list_variables;
}
IVariable* CVariableOutputListVariables::getIVariable(){
    return this;
}
bool CVariableOutputListVariables::toBool(){
    return false;
}


QVariantMap CVariableOutputListVariables::serialize(){
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_integer"));
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    return mapSerialise;
}
