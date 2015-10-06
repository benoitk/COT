#include "CComJBus.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "IComObserver.h"
#include "CModelExtensionCard.h"
#include "cotautomate_debug.h"
#include "IOrgan.h"
#include <QThread>

#include <cstring>
#include <cerrno>

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

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(modbus_t *ctx, QThread *thread)
        : QObject(Q_NULLPTR)
        , m_ctx(ctx)
    {
        qDebug() << "moveThread Worker";
        moveToThread(thread);
        connect(thread, &QThread::started,
                this, &Worker::run);
        connect(thread, &QThread::finished,
                this, &Worker::deleteLater);
    }

signals:
    void connected(bool success);

private:
    void run()
    {
        if (modbus_connect(m_ctx) == -1) {
            qWarning("Failed to connect to com bus: %s\n", modbus_strerror(errno));
            connected(false);
            return;
        }
        emit connected(true);
        // TODO: receive messages, reply to them
    }

    modbus_t *m_ctx;
};
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

CComJBus::CComJBus(const QVariantMap &mapCom, QObject *parent)
    : ICom(parent)
    , m_ctx(Q_NULLPTR)
    , m_modbusThread(new QThread(this))
    , m_slave(-1)
    , m_type(e_type_com_unknow)
{
    m_ip = mapCom.value(QStringLiteral("ip")).toString();
    m_name = mapCom.value(QStringLiteral("name")).toString();
    if(m_name.isEmpty()) {
        qCDebug(COTAUTOMATE_LOG) << "CComJBus not named.";
        m_name = QStringLiteral("Com not named");
    }

    m_type = stringToComType(mapCom.value(QStringLiteral("type")).toString());
    switch(m_type)
    {
    case e_type_jbus_over_tcpip:
        m_ctx.reset(initTcp(mapCom, modbus_new_rtutcp));
        break;
    case e_type_jbus:
        m_ctx.reset(initRtu(mapCom));
        break;
    case e_type_tcpip:
        m_ctx.reset(initTcp(mapCom, modbus_new_tcp));
        break;
    case e_type_com_unknow:
        qCDebug(COTAUTOMATE_LOG) << "CComJBus type unknow:" << mapCom;
    }

    bool ok = false;
    const int slave = mapCom.value(QStringLiteral("slave")).toInt(&ok);
    if (ok && slave >= 0) {
        m_slave = slave;
    }

    if (m_ctx) {
        if (mapCom.value(QStringLiteral("debug")).toBool())
            modbus_set_debug(m_ctx.data(), 1);

        initializeModbus();
    } else {
        // emit a delayed connection-failed signal, so that people can instantiate the object,
        // connect to the connected signal, and still get their slot called.
        QMetaObject::invokeMethod(this, "connected", Qt::QueuedConnection, Q_ARG(bool, false));
    }
}

CComJBus::~CComJBus()
{
    m_modbusThread->quit();
    m_modbusThread->wait();
}

void CComJBus::initializeModbus()
{
    //control erreus
    if (modbus_set_error_recovery(m_ctx.data(),  static_cast<modbus_error_recovery_mode>(MODBUS_ERROR_RECOVERY_LINK |   MODBUS_ERROR_RECOVERY_PROTOCOL)) == -1)
    {
        qCDebug(COTAUTOMATE_LOG) << "CComJBus failed to set error recovery:"    << modbus_strerror(errno);
    }
    timeval timeout = {1, 0};
    modbus_set_response_timeout(m_ctx.data(), &timeout);
    //fin control erreur

    // -1 == m_slave indicates master coms
    if (m_slave >= 0)
        modbus_set_slave(m_ctx.data(), m_slave);

    Worker *worker = new Worker(m_ctx.data(), m_modbusThread);
    connect(worker, &Worker::connected,
            this, [this] (bool success) {
                if (!success) {
                    m_ctx.reset();
                }
                emit connected(success);
            });
    m_modbusThread->start();    

}

QVariant CComJBus::readData(){
    return QVariant();
}
QVariant CComJBus::readData(IVariableInput* arg_input){
    QMutexLocker lock(&m_mutex);

    const int address = arg_input->getOrganAddr().toInt(0,16);

//    switch (arg_input->getIVariable()->getType())
    switch(arg_input->getOrgan()->getType())
    {
    case organ_type_input_bool:
        return readBool(address, Input);
    case organ_type_input_int:
        return readInt(address, Input);
    case organ_type_input_float:
        return readFloat(address, Input);
//    case type_unknow:
    default:
        break;
    }
    return QVariant();
}
//permet de faire des commande passive ou active avec les booléens
void CComJBus::writeData(bool value, const QString& addr){
    QMutexLocker lock(&m_mutex);
    writeBool(addr.toInt(0,16), value);
}
void CComJBus::writeData(IVariableOutput* arg_output)
{
    QMutexLocker lock(&m_mutex);

    const int address = arg_output->getOrganAddr().toInt(0,16);
    IVariable* variable = arg_output->getIVariable();
    switch (variable->getType())
    {
    case e_type_bool:
        writeBool(address, variable->toBool());
        break;
    case e_type_int:
        writeInt(address, variable->toInt());
        break;
    case e_type_float:
        writeFloat(address, variable->toFloat());
        break;
    case e_type_unknow:
    default:
        break;
    }
}

CComJBus::BitArray CComJBus::readNBitsFunction1(int addrVar, int nbBitsToRead)
{
    BitArray ret(nbBitsToRead);
    std::fill(ret.begin(), ret.end(), 0);
    if (!m_ctx)
        qCDebug(COTAUTOMATE_LOG) << "Cannot read data from uninitialized modbus context.";
    else if (modbus_read_bits(m_ctx.data(), addrVar, nbBitsToRead, ret.data()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to read" << nbBitsToRead << "bits from" << addrVar << ':' << modbus_strerror(errno);
    return ret;
}

void CComJBus::writeNBitsFunction15(int addrVar, const BitArray &data)
{
    if (!m_ctx)
        qCDebug(COTAUTOMATE_LOG) << "Cannot write data to uninitialized modbus context.";
    else if (modbus_write_bits(m_ctx.data(), addrVar, data.size(), data.constData()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to write" << data.size() << "bits to" << addrVar << ':' << modbus_strerror(errno) << " IP :" << m_ip;
}

CComJBus::WordArray CComJBus::readNWordsFunction3(int addrVar, int nbWordsToRead)
{
    WordArray ret(nbWordsToRead);
    std::fill(ret.begin(), ret.end(), 0);
    if (!m_ctx)
        qCDebug(COTAUTOMATE_LOG) << "Cannot read data from uninitialized modbus context.";
    else if (modbus_read_registers(m_ctx.data(), addrVar, nbWordsToRead, ret.data()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to read" << nbWordsToRead << "words from" << addrVar << ':' << modbus_strerror(errno);
    return ret;

}

void CComJBus::writeNWordsFunction16(int addrVar, const WordArray &data)
{
    if (!m_ctx)
        qCDebug(COTAUTOMATE_LOG) << "Cannot write data to uninitialized modbus context.";
    else if (modbus_write_registers(m_ctx.data(), addrVar, data.size(), data.constData()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to write" << data.size() << "words to" << addrVar << ':' << modbus_strerror(errno);
}

CComJBus::BitArray CComJBus::readNInputBitsFunction2(int addrVar, int nbBitsToRead)
{
    BitArray ret(nbBitsToRead);
    std::fill(ret.begin(), ret.end(), 0);
    if (!m_ctx)
        qCDebug(COTAUTOMATE_LOG) << "Cannot read data from uninitialized modbus context.";
    else if (modbus_read_input_bits(m_ctx.data(), addrVar, nbBitsToRead, ret.data()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to read" << nbBitsToRead << "input bits from" << addrVar << ':' << modbus_strerror(errno);
    return ret;
}

CComJBus::WordArray CComJBus::readNInputWordsFunction4(int addrVar, int nbWordsToRead)
{
    WordArray ret(nbWordsToRead);
    std::fill(ret.begin(), ret.end(), 0);
    if (!m_ctx)
        qCDebug(COTAUTOMATE_LOG) << "Cannot read data from uninitialized modbus context.";
    else if (modbus_read_input_registers(m_ctx.data(), addrVar, nbWordsToRead, ret.data()) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to read" << nbWordsToRead << "input words from" << addrVar << ':' << modbus_strerror(errno);
    return ret;
}

void CComJBus::writeBitFunction5(int addrVar, bool bit)
{
    if (!m_ctx)
        qCDebug(COTAUTOMATE_LOG) << "Cannot write data to uninitialized modbus context.";
    else if (modbus_write_bit(m_ctx.data(), addrVar, bit) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to write bit to" << addrVar << ':' << modbus_strerror(errno);
}

void CComJBus::writeWordFunction6(int addrVar, int word)
{
    if (!m_ctx)
        qCDebug(COTAUTOMATE_LOG) << "Cannot write data to uninitialized modbus context.";
    else if (modbus_write_register(m_ctx.data(), addrVar, word) == -1)
        qCDebug(COTAUTOMATE_LOG) << "Failed to write word to" << addrVar << ':' << modbus_strerror(errno);
}

bool CComJBus::readBool(int addrVar, Type type)
{
    if (type == Output)
        return readNBitsFunction1(addrVar, 1).at(0);
    else
        return readNInputBitsFunction2(addrVar, 1).at(0);
}

void CComJBus::writeBool(int addrVar, bool value)
{
    //BitArray bits(1);
    //bits[0] = value;
    //writeNBitsFunction15(addrVar, bits);
    writeBitFunction5(addrVar, value);
}

CComJBus::WordArray CComJBus::readNWords(int addrVar, int nbWordsToRead, Type type)
{
    return type == Output
        ? readNWordsFunction3(addrVar, nbWordsToRead)
        : readNInputWordsFunction4(addrVar, nbWordsToRead);
}

int CComJBus::readInt(int addrVar, Type type)
{
    const WordArray& words = readNWords(addrVar, sizeof(int) / sizeof(uint16_t), type);
    int value;
    memcpy(&value, words.data(), sizeof(int));
    return value;
}

void CComJBus::writeInt(int addrVar, int value)
{
    WordArray words(sizeof(int) / sizeof(uint16_t));
    memcpy(words.data(), &value, sizeof(int));
    //writeNWordsFunction16(addrVar, words);
    //Fonction 16 non fonctionnel sur deuxième 4-20
    writeWordFunction6((short int)addrVar, value);
}

float CComJBus::readFloat(int addrVar, Type type)
{
    const WordArray& words = readNWords(addrVar, sizeof(int) / sizeof(uint16_t), type);
    return modbus_get_float(words.data());
}

void CComJBus::writeFloat(int addrVar, float value)
{
    WordArray words(sizeof(float) / sizeof(uint16_t));
    modbus_set_float(value, words.data());
    writeNWordsFunction16(addrVar, words);
}

void CComJBus::triggerUpdateAllData(){

}

void CComJBus::addVariableOnDataTable(IVariableInput* arg_varInput){
    m_mapInputTable.insert(arg_varInput->getOrganAddr().toInt(), arg_varInput);

}
void CComJBus::addVariableOnDataTable(IVariableOutput* arg_varOutput){
    m_mapOutputTable.insert(arg_varOutput->getOrganAddr().toInt(), arg_varOutput);
}

QString CComJBus::getName()const{
    return m_name;
}
enumComType CComJBus::getType()const{
    return m_type; //typer slave et master ?
}
QVariantMap CComJBus::serialize(){
    QVariantMap mapSerialize;
    mapSerialize.insert(QStringLiteral("name"), m_name);
    mapSerialize.insert(QStringLiteral("type"),comTypeToString(m_type) );
    mapSerialize.insert(QStringLiteral("slave"), m_slave);
    mapSerialize.insert(QStringLiteral("ip"), m_ip);
    mapSerialize.insert(QStringLiteral("port"), 502); //?Pas utilisé le port ?
    mapSerialize.insert(QStringLiteral("debug"), false);

    return mapSerialize;
}
#include "CComJBus.moc"
