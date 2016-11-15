#include "CComJBus.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "IComObserver.h"
#include "CModelExtensionCard.h"
#include "cotautomate_debug.h"
#include "IOrgan.h"
#include "CVariableFloat.h"
#include <QThread>
#include <QDir>

#include <cstring>
#include <cerrno>
#include <modbus-data.c>
#include "unistd.h"

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
    explicit Worker(modbus_t *ctx, QThread *thread, CComJBus* jbus)
        : QObject(Q_NULLPTR)
        , m_ctx(ctx)
        , m_jbus(jbus)
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
        if(m_jbus->isMaster()){


            if (modbus_connect(m_ctx) == -1) {
                qWarning("Failed to connect to com bus: %s\n", modbus_strerror(errno));
                connected(false);
                return;
            }
            emit connected(true);
        }
        else{
            m_jbus->runJBusReceiveReply();
        }
    }
    CComJBus * m_jbus;
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
bool CComJBus::isMaster()const{
    return m_masterMode;
}
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
    m_masterMode = mapCom.value(QStringLiteral("is_master")).toBool();
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

    Worker *worker = new Worker(m_ctx.data(), m_modbusThread, this);
    connect(worker, &Worker::connected,
            this, [this] (bool success) {
        if (!success) {
            m_ctx.reset();
        }
        emit connected(success);
    });
    m_modbusThread->start();

}

//appeler uniquement en mode slave (!isMaster())
void CComJBus::runJBusReceiveReply(){

    for(;;){
        int socket = -1;


        if (m_type == e_type_jbus_over_tcpip) {
            socket = modbus_connect(m_ctx.data()) ;
            if (socket == -1) {
                fprintf(stderr, "Unable to connect %s\n", modbus_strerror(errno));
                return;
            }
        } else {
            socket = modbus_tcp_listen(m_ctx.data(), 1);

            if (socket != -1 && modbus_tcp_accept(m_ctx.data(), &socket) == -1) {
                fprintf(stderr, "modbus_tcp_accept failed: %s\n", modbus_strerror(errno));
                return;
            }
        }

        if(socket != -1){

            for (;;) {
                uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];

                int rc = modbus_receive(m_ctx.data(), query);
                if (rc == -1) {
                    fprintf(stderr, "modbus_receive failed: %s\n", modbus_strerror(errno));
                    break;
                }
                else
                {

                    modbus_mapping_t mapping = {
                        m_dataTableBits.size(), m_dataTableBits.size(), m_dataTableWords.size(), m_dataTableWords.size(),
                        m_dataTableBits.data(), m_dataTableBits.data(), m_dataTableWords.data(), m_dataTableWords.data(),
                        false, false, false, false
                    };
                    //        modbus_mapping_t mapping = {
                    //            m_dataTableBits.size(), m_dataTableInputBits.size(), m_dataTableInputWords.size(), m_dataTableWords.size(),
                    //            m_dataTableBits.data(), m_dataTableInputBits.data(), m_dataTableInputWords.data(), m_dataTableWords.data(),
                    //            false, false, false, false
                    //        };
                    m_mutex.lock(); //protection de la table JBus
                    rc = modbus_reply(m_ctx.data(), query, rc, &mapping);
                    m_mutex.unlock();
                    if (rc == -1) {
                        fprintf(stderr, "modbus_reply failed: %s\n", modbus_strerror(errno));
                        break;
                    }

                    if(mapping.tab_bits_updated){
                        for(int i =0; i < m_listDataTableVariableBool.count(); ++i) {
                            m_listDataTableVariableBool.value(i)->setValue(m_dataTableBits.at(i));
                        }
                        mapping.tab_bits_updated = false;
                    }
                    if(mapping.tab_registers_updated){
                        for(int i =0; i < m_listDataTableVariableNumeric.count(); ++i) {
                            WordArray words; //sert pour la gestion des flottant et des entiers large
                            IVariable* var = m_listDataTableVariableNumeric.value(i);
                            if(var->getType() == e_type_float){
                                //si un jour on se décide à gérer les flotants avec le JBus, remplacer le code suivant avec celui en commentaire
                                float fValue = m_dataTableWords.value(i);
                                for(int k=0; k<(dynamic_cast<CVariableFloat*>(var))->getPrecision();++k)
                                    fValue = fValue/10;

                                //                                for(int j=0; j<sizeof(float) / sizeof(uint16_t); ++j)
                                //                                    words.append(m_dataTableWords.value(i+j));
                                //                                float fValue = modbus_get_float(words.data());
                                var->setValue(fValue);
                            }
                            else if(var->getType() == e_type_int){
                                //si un jour on se décide à gérer les entiers de plus de 16bits, remplacer le code suivant avec celui en commentaire
                                int iValue = m_dataTableWords.value(i);
                                //                                for(int j=0; j<sizeof(int) / sizeof(uint16_t); ++j)
                                //                                    words.append(m_dataTableWords.value(i+j));
                                //                                int iValue = 0;
                                //                                for(int k=0; k<words.count();++k)
                                //                                    iValue += ((int)words.at(k)) << (16*k);
                                var->setValue(iValue);
                            }

                        }
                    }
                    mapping.tab_registers_updated = false;
                }
                QThread::msleep(100);
            }
        }
        QThread::msleep(1000);
        close(socket);

    }
    QThread::msleep(1000);
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

void CComJBus::addVariableInputOnDataTable(IVariableInput* arg_varInput){
    m_mapInputTable.insert(arg_varInput->getOrganAddr().toInt(), arg_varInput);

}
void CComJBus::addVariableOutputOnDataTable(IVariableOutput* arg_varOutput){
    m_mapOutputTable.insert(arg_varOutput->getOrganAddr().toInt(), arg_varOutput);
}

void CComJBus::addVariableOnDataTable(IVariable* arg_var){
    QMutexLocker lock(&m_mutex);

    switch (arg_var->getType()) {
    case e_type_alarm:
    case e_type_bool:
        arg_var->setAddress(m_dataTableBits.count());
        m_dataTableBits.append(arg_var->toBool());
        m_listDataTableVariableBool.append(arg_var);

        break;
    case e_type_float:
    {
        //si un jour on se décide à gérer les flotants avec le JBus, remplacer le code suivant avec celui en commentaire
        float valueTemp = arg_var->toFloat();
        for(int i=0; i<((CVariableFloat*)arg_var)->getPrecision();++i)
            valueTemp = valueTemp * 10;
        short int value = valueTemp;
        arg_var->setAddress(m_dataTableWords.count());
        m_dataTableWords.append(value);
        //        WordArray words(sizeof(float) / sizeof(uint16_t));
        //        modbus_set_float(arg_var->toFloat(), words.data());
        //        arg_var->setAddress(m_dataTableWords.count());
        //        for(int i=0; i < words.count(); ++i){
        //            m_dataTableWords.append(words.at(i));;
        //        }

        m_listDataTableVariableNumeric.append(arg_var);
    }
        break;
    case e_type_int:
    {
        //si un jour on se décide à gérer les entiers de plus de 16bits, remplacer le code suivant avec celui en commentaire
        short int value = arg_var->toInt();
        arg_var->setAddress(m_dataTableWords.count());
        m_dataTableWords.append(value);
        //        WordArray words(sizeof(int) / sizeof(uint16_t));
        //        int value = arg_var->toInt();
        //        memcpy(words.data(), &value, sizeof(int));
        //        arg_var->setAddress(m_dataTableWords.count());
        //        for(int i=0; i < words.count(); ++i){
        //            m_dataTableWords.append(words.at(i));;
        //        }
        m_listDataTableVariableNumeric.append(arg_var);
    }
        break;
    default:
        break;
    }
    connect(arg_var, &IVariable::signalVariableChanged, this, &CComJBus::slotVariableUpdated);

}
void CComJBus::slotVariableUpdated(IVariable* arg_var){
    QMutexLocker lock(&m_mutex);
    switch (arg_var->getType()) {
    case e_type_alarm:
    case e_type_bool:
        if(arg_var->getAddress() < m_dataTableBits.count()){

            int wordAddr = arg_var->getAddress() / 16;
            int value = m_dataTableWords.value(wordAddr);
            if(arg_var->toBool())
                value |=  arg_var->toInt() << (arg_var->getAddress()%16);
            else
                value &=  ((1 << (arg_var->getAddress()%16)) ^ 0xFF);
            m_dataTableWords.replace(wordAddr, value);

            m_dataTableBits.replace(arg_var->getAddress(), arg_var->toBool());
        }
        break;
    case e_type_float:
    {
        if(arg_var->getAddress() < m_dataTableWords.count()){
            float valueTemp = arg_var->toFloat();
            for(int i=0; i<((CVariableFloat*)arg_var)->getPrecision();++i)
                valueTemp = valueTemp * 10;
            short int value = valueTemp;
            m_dataTableWords.replace(arg_var->getAddress(), value);
            //            WordArray words(sizeof(float) / sizeof(uint16_t));
            //            modbus_set_float(arg_var->toFloat(), words.data());
            //            for(int i=0; i < words.count(); ++i){
            //                m_dataTableWords.replace(arg_var->getAddress()+i, words.at(i));
            //            }
        }
    }
        break;
    case e_type_int:
    {
        if(arg_var->getAddress() < m_dataTableWords.count()){
            //si un jour on se décide à gérer les entiers de plus de 16bits, remplacer le code suivant avec celui en commentaire
            short int value = arg_var->toInt();
            m_dataTableWords.replace(arg_var->getAddress(),value);

            //            WordArray words(sizeof(int) / sizeof(uint16_t));
            //            int value = arg_var->toInt();
            //            memcpy(words.data(), &value, sizeof(int));
            //            for(int i=0; i < words.count(); ++i){
            //                m_dataTableWords.replace(arg_var->getAddress()+i, words.at(i));
            //            }
        }
    }
        break;
    default:
        break;
    }
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

void CComJBus::generateDocumentation(){
    QString dirPath = QString(LOG_SOURCE_DIRECTORY);
    QDir dir = QDir(dirPath);
    if(!dir.exists()){
        dir.mkdir(dirPath);
    }
    QString path = dirPath+ "/JBusTable.tex";
    QFile data(path);
    if(data.exists())
        data.remove();
    if (data.open(QFile::Append)) {
        QTextStream out(&data);
        out.setCodec("UTF-8");
        out << "\\documentclass[a4paper,10pt,oneside]{article}"<< endl;
        out << "\\title{"<< QString(tr("JBUS Data table")) << "}"<< endl;
        out << "\\author{" << QString(tr("Generated by SERES TOC")) << "}"<< endl;
        out << "\\begin{document}"<< endl;
        out << "\\maketitle"<< endl;

        //Bits data table
        out << QString(tr("Input/Ouput bits data table")) << endl;
        out << "\\begin{tabular}{|l|l|l|}"<< endl;
        out << "\\hline"<< endl;
        out << "\\textbf{Data Name} & \\textbf{Data type} & \\textbf{Address} \\\\"<< endl;
        out << "\\hline"<< endl;
        foreach(IVariable* arg_var, m_listDataTableVariableBool){

            out << arg_var->getLabel() << " & "
                << "argvargetType()"<< " & ";
            out << "0x";
            //addresse en hexa
            QString addr = QString::number( arg_var->getAddress(), 16).rightJustified(4, '0');
            out << addr  << " \\\\" << endl;
            out << "\\hline" << endl;

        }
        out << "\\end{tabular}\\end{document}" << endl;

        //Words data table
        out << QString(tr("Input/Ouput words data table")) << endl;
        out << "\\begin{tabular}{|l|l|l|}"<< endl;
        out << "\\hline"<< endl;
        out << "\\textbf{Data Name} & \\textbf{Data type} & \\textbf{Address} \\\\"<< endl;
        out << "\\hline"<< endl;
        foreach(IVariable* arg_var, m_listDataTableVariableNumeric){

            out << arg_var->getLabel() << " & "
                << "argvargetType()"<< " & ";
            out << "0x";
            //addresse en hexa
            QString addr = QString::number( arg_var->getAddress(), 16).rightJustified(4, '0');
            out << addr  << " \\\\" << endl;
            out << "\\hline" << endl;

        }
        out << "\\end{tabular}\\end{document}" << endl;
    }else{
        qDebug() << "Can't open file";
    }
    data.close();

}

 #include "CComJBus.moc"
