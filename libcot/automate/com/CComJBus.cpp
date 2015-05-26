#include "CComJBus.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "IComObserver.h"
#include "CModelExtensionCard.h"
#include "cotautomate_debug.h"

#include <modbus.h>

CComJBus::CComJBus(QObject *parent)
    : ICom(parent)
    , m_ctx(0)
    , m_uart(0)
    , m_numSlave(0)
    , m_type(type_com_unknow)
{

}
CComJBus::CComJBus(const QVariantMap& mapCom)
    : ICom()
    , m_ctx(0)
    , m_uart(0)
    , m_numSlave(0)
    , m_type(type_com_unknow)
{
    m_name = mapCom.value(QStringLiteral("name")).toString();
    if(m_name.isEmpty()) {
        qCDebug(COTAUTOMATE_LOG) << "CComJBus not named.";
        m_name = QStringLiteral("Com not named");
    }

    const QString type = mapCom.value(QStringLiteral("type")).toString();
    if(type == QLatin1String("jbus_over_tcpip"))
        m_type = type_jbus_over_tcpip;
    else if (type == QLatin1String("jbus"))
        m_type = type_jbus;
    else
        qCDebug(COTAUTOMATE_LOG) << "CComJBus type unknow:" << type;

    //TO DO : fill datas
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

    switch (arg_input->getIVariable()->getType())
    {
    case type_bool:
        bitArray = readNBitsFunction1(arg_input->getOrganneAddr().toInt(), 1);
        if(!bitArray.isEmpty()){
            returnedVar = bitArray.at(0);
        }
        break;
    case type_int:
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
    case type_float:
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
    case type_unknow:
    default:
        break;
    }
    return QVariant();
}
void CComJBus::writeData(IVariableOutput* arg_output){
    switch (arg_output->getIVariable()->getType())
    {
    case type_bool:
        writeNBitsFunction15(arg_output->getOrganneAddr().toInt(), QBitArray(1,arg_output->getIVariable()->toInt()));
        break;
    case type_int:
        readNWordsFunction3(arg_output->getOrganneAddr().toInt(), 2);
        break;
    case type_float:
        readNWordsFunction3(arg_output->getOrganneAddr().toInt(), 4);
        break;
    case type_unknow:
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

QString CComJBus::getName()const{
    return m_name;
}
comType CComJBus::getType()const{
    return m_type; //typer slave et master ?
}


