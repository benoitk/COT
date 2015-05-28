#include "CComJBus.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "IComObserver.h"
#include "CModelExtensionCard.h"
#include "cotautomate_debug.h"

#include <cstring>

namespace {
modbus_t *initRtu(const QVariantMap &options)
{
    QByteArray device = options.value(QStringLiteral("device")).toByteArray();
    if(device.isEmpty()){
        qCWarning(COTAUTOMATE_LOG) << "missing device name:" << options;
        return 0;
    }
    bool ok = false;
    int baudrate = options.value(QStringLiteral("baudrate")).toInt(&ok);
    if(!ok){
        qCWarning(COTAUTOMATE_LOG) << "missing baud rate:" << options;
        return 0;
    }
    int data_bit = options.value(QStringLiteral("data")).toInt(&ok);
    if(!ok){
        qCWarning(COTAUTOMATE_LOG) << "missing data bit:" << options;
        return 0;
    }
    int stop_bit = options.value(QStringLiteral("stop")).toInt(&ok);
    if(!ok){
        qCWarning(COTAUTOMATE_LOG) << "missing stop bit:" << options;
        return 0;
    }
    modbus_t *ret = modbus_new_rtu(device.constData(), baudrate, 'N', data_bit, stop_bit);
    if(!ret)
        qCWarning(COTAUTOMATE_LOG) << "failed to initialize modbus over rtu:" << modbus_strerror(errno);
    return ret;
}

template<typename InitFunction>
modbus_t *initTcp(const QVariantMap &options, InitFunction init)
{
    QByteArray ip = options.value(QStringLiteral("ip")).toByteArray();
    if(ip.isEmpty()){
        qCWarning(COTAUTOMATE_LOG) << "missing ip:" << options;
        return 0;
    }
    bool ok = false;
    int port = options.value(QStringLiteral("port")).toInt(&ok);
    if(!ok){
        qCWarning(COTAUTOMATE_LOG) << "missing port:" << options;
        return 0;
    }
    modbus_t *ret = init(ip.constData(), port);
    if(!ret)
        qCWarning(COTAUTOMATE_LOG) << "failed to initialize modbus over tcp:" << modbus_strerror(errno);
    return ret;
}
}

struct CComJBus::FreeModbus
{
    static inline void cleanup(modbus_t *ctx)
    {
        if (ctx) {
            modbus_close(ctx);
            modbus_free(ctx);
        }
    }
};

struct CComJBus::FreeModbusMapping
{
    static inline void cleanup(modbus_mapping_t *mapping)
    {
        if (mapping)
            modbus_mapping_free(mapping);
    }
};

CComJBus::CComJBus(const QVariantMap &mapCom, QObject *parent)
    : ICom(parent)
    , m_ctx(Q_NULLPTR)
    , m_slave(-1)
    , m_type(type_com_unknow)
{
    m_name = mapCom.value(QStringLiteral("name")).toString();
    if(m_name.isEmpty()) {
        qCDebug(COTAUTOMATE_LOG) << "CComJBus not named.";
        m_name = QStringLiteral("Com not named");
    }

    m_type = stringToComType(mapCom.value(QStringLiteral("type")).toString());
    switch(m_type)
    {
    case type_jbus_over_tcpip:
        m_ctx.reset(initTcp(mapCom, modbus_new_rtutcp));
        break;
    case type_jbus:
        m_ctx.reset(initRtu(mapCom));
        break;
    case type_tcpip:
        m_ctx.reset(initTcp(mapCom, modbus_new_tcp));
        break;
    case type_com_unknow:
        qCDebug(COTAUTOMATE_LOG) << "CComJBus type unknow:" << mapCom;
    }

    bool ok = false;
    const int slave = mapCom.value(QStringLiteral("slave")).toInt(&ok);
    if (ok && slave >= 0) {
        m_slave = slave;
    }

    if (m_ctx)
        initializeModbus();
}

CComJBus::~CComJBus()
{
}

void CComJBus::initializeModbus()
{
    // TODO: disable
    modbus_set_debug(m_ctx.data(), 1);

    // -1 == m_slave indicates master coms
    if (m_slave >= 0)
        modbus_set_slave(m_ctx.data(), m_slave);

    if (modbus_connect(m_ctx.data()) == -1) {
        qWarning("Failed to connect to com bus: %s\n", modbus_strerror(errno));
        m_ctx.reset();
        return;
    }

    m_mapping.reset(modbus_mapping_new(MODBUS_MAX_READ_BITS, 0, MODBUS_MAX_READ_REGISTERS, 0));
    if (!m_mapping) {
        qWarning("Failed to allocate the mapping: %s\n", modbus_strerror(errno));
        m_ctx.reset();
        return;
    }
}

QVariant CComJBus::readData(){
    return QVariant();
}
QVariant CComJBus::readData(IVariableInput* arg_input){
    BitArray bitArray;
    WordArray wordArray;
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
            wordArray = readNWordsFunction3(arg_input->getOrganneAddr().toInt(), 2);

            char byte;
            int value =0;
            int i=0;
            foreach(byte, wordArray){
                int value = value + ((byte << (8*i++)) & 0xffff);
            }
            returnedVar = value;
            break;
        }
    case type_float:
        {
            wordArray = readNWordsFunction3(arg_input->getOrganneAddr().toInt(), 4);
            char byte;
            float fValue =0;
            int i=0;
            foreach(byte, wordArray){
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
        writeNBitsFunction15(arg_output->getOrganneAddr().toInt(), BitArray(1, arg_output->getIVariable()->toInt()));
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

CComJBus::BitArray CComJBus::readNBitsFunction1(int addrVar, int nbBitsToRead)
{
    BitArray ret(nbBitsToRead);
    if (modbus_read_bits(m_ctx.data(), addrVar, nbBitsToRead, ret.data()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to read" << nbBitsToRead << "bits from" << addrVar << ':' << modbus_strerror(errno);
    return ret;
}

void CComJBus::writeNBitsFunction15(int addrVar, const BitArray &data)
{
    if (modbus_write_bits(m_ctx.data(), addrVar, data.size(), data.constData()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to write" << data.size() << "bits to" << addrVar << ':' << modbus_strerror(errno);
}

CComJBus::WordArray CComJBus::readNWordsFunction3(int addrVar, int nbWordsToRead)
{
    WordArray ret(nbWordsToRead);
    if (modbus_read_registers(m_ctx.data(), addrVar, nbWordsToRead, ret.data()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to read" << nbWordsToRead << "words from" << addrVar << ':' << modbus_strerror(errno);
    return ret;

}

void CComJBus::writeNWordsFunction16(int addrVar, const WordArray &data)
{
    if (modbus_write_registers(m_ctx.data(), addrVar, data.size(), data.constData()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to write" << data.size() << "words from" << addrVar << ':' << modbus_strerror(errno);
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
