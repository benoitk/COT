#include "CComUnknow.h"

#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "IComObserver.h"
#include "CModelExtensionCard.h"
#include "ICom.h"
CComUnknow::CComUnknow(QObject *parent): ICom(parent){

}
CComUnknow::CComUnknow(): ICom(){

}
CComUnknow::~CComUnknow()
{

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

void CComUnknow::addVariableOnDataTable(IVariableInput* arg_varInput){

}
void CComUnknow::addVariableOnDataTable(IVariableOutput* arg_varOutput){
}

QString CComUnknow::getName()const{
    return QStringLiteral("Unknow com");
}
comType CComUnknow::getType()const{
    return type_com_unknow; 
}


