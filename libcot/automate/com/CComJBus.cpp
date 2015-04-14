#include "CComJBus.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "IComObserver.h"
#include "CModelExtensionCard.h"

CComJBus::CComJBus(QObject *parent)
	: ICom(parent)
{

}
CComJBus::~CComJBus()
{

}
QVariant CComJBus::readData(){
	return QVariant();
}
QVariant CComJBus::readData(IVariableInput* arg_input){
	QBitArray bitArray;
	QList<char> byteArray;
	QVariant returnedVar;

	switch (arg_input->getTypeOrganne())
	{
	case type_input_bool:
		bitArray = readNBitsFunction1(arg_input->getOrganneAddr().toInt(), 1);
		if(!bitArray.isEmpty()){
			returnedVar = bitArray.at(0);
		}
		break;
	case type_input_int:
		{
			byteArray = readNWordsFunction3(arg_input->getOrganneAddr().toInt(), 2);	
		
			char byte;
			int value =0;
			int i=0;
			foreach(byte, byteArray){
				int value = value + ((byte << (8*i++)) & 0xffff);
			}
			returnedVar = value;
			break;
		}
	case type_input_float:
		{
			byteArray = readNWordsFunction3(arg_input->getOrganneAddr().toInt(), 4);
			char byte;
			float fValue =0;
			int i=0;
			foreach(byte, byteArray){
				int fValue = fValue + ((byte << (8*i++)) & 0xffff);
			}
			returnedVar = fValue;
			break;
		}
	case type_input_unknow:
	default:
		break;
	} 
	return QVariant();
}
void CComJBus::writeData(IVariableOutput* arg_output){
	switch (arg_output->getTypeOrganne())
	{
	case type_output_bool:
		writeNBitsFunction15(arg_output->getOrganneAddr().toInt(), QBitArray(1,arg_output->getIVariable()->toInt()));
		break;
	case type_output_int:
		readNWordsFunction3(arg_output->getOrganneAddr().toInt(), 2);
		break;
	case type_output_float:
		readNWordsFunction3(arg_output->getOrganneAddr().toInt(), 4);
		break;
	case type_output_unknow:
	default:
		break;
	} 

}

QBitArray CComJBus::readNBitsFunction1(int addrVar, int nbBitsToRead){
	return QBitArray();
}
void CComJBus::writeNBitsFunction15(int addrVar, const QBitArray &data){

}
QList<char> CComJBus::readNWordsFunction3( int addrVar, int nbBytesToRead){
	QList<char> temp;
	return temp;

}
void CComJBus::writeNWordsFunction16( int addrVar, const QList<char> &data){

}

void CComJBus::triggerUpdateAllData(){

}

void CComJBus::addVariableOnDataTable(IVariableInput* arg_varInput){
	m_mapInputTable.insert(arg_varInput->getOrganneAddr().toInt(), arg_varInput);

}
void CComJBus::addVariableOnDataTable(IVariableOutput* arg_varOutput){
	m_mapOutputTable.insert(arg_varOutput->getOrganneAddr().toInt(), arg_varOutput);
}


