#include "CComUnknow.h"

#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "IComObserver.h"
#include "CModelExtensionCard.h"
#include "ICom.h"
CComUnknow::CComUnknow(QObject *parent): ICom(parent){

}
CComUnknow::~CComUnknow()
{

}


void CComUnknow::writeData(bool, const QString&){

}

QVariant CComUnknow::readData(){
    return QVariant("CComUnknow::readData()");
}
QVariant CComUnknow::readData(IVariableInput* arg_input){
    return QVariant("CComUnknow::readData(IVariableInput* arg_input)");
}
void CComUnknow::writeData(IVariableOutput* arg_output){
}

void CComUnknow::triggerUpdateAllData(){

}

void CComUnknow::addVariableInputOnDataTable(IVariableInput* arg_varInput){

}
void CComUnknow::addVariableOutputOnDataTable(IVariableOutput* arg_varOutput){
}
void CComUnknow::addVariableOnDataTable( IVariable* arg_varOutput){
}

QString CComUnknow::getName()const{
    return QStringLiteral("Unknow com");
}
enumComType CComUnknow::getType()const{
    return e_type_com_unknow;
}
void CComUnknow::generateDocumentation(){
    //TODO générer un fichier d'erreur
}

