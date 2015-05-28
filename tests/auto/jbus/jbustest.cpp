#include <qtest.h>

#include <QObject>
#include "CComJBus.h"

#include <QDebug>
#include <QTcpServer>
#include <QHostAddress>
#include <QBitArray>

#include <thread>
#include <future>

#ifdef Q_OS_LINUX
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

class PseudoTerminal
{
public:
    PseudoTerminal()
        : m_master(-1)
        , m_name(Q_NULLPTR)
    {
    }

    void init()
    {
        m_master = posix_openpt(O_RDWR | O_NOCTTY);
        if (m_master == -1 || grantpt(m_master) == -1 || unlockpt(m_master) == -1) {
            qWarning() << "Failed to open pseudo-tty";
            return;
        }
        m_name = ptsname(m_master);
    }

    ~PseudoTerminal()
    {
        if (m_master >= 0)
            close(m_master);
    }

    const char *name() const
    {
        return m_name;
    }

private:
    int m_master;
    char *m_name;
};

#else

class PseudoTerminal
{
public:
    void init() {}
    const char *name() const
    {
        return Q_NULLPTR;
    }
};
#endif

class JBusTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void testInitialize_data();
    void testInitialize();

    void testRtu();
    void testTcpip();

private:
    bool isInitialized(const CComJBus &bus) const
    {
        return bus.m_ctx.data() && bus.m_mapping.data();
    }

    PseudoTerminal m_pty;
    QTcpServer m_tcp;
};

void JBusTest::initTestCase()
{
    m_pty.init();
    QVERIFY(m_tcp.listen(QHostAddress::LocalHost, 12345));
}

void JBusTest::testInitialize_data()
{
    QTest::addColumn<QVariantMap>("map");
    QTest::addColumn<QString>("name");
    QTest::addColumn<comType>("type");
    QTest::addColumn<bool>("initialized");

    {
        QVariantMap map;
        map["name"] = "com_jbus_tcpip_master";
        map["type"] = "jbus_over_tcpip";
        map["ip"] = m_tcp.serverAddress().toString();
        map["port"] = m_tcp.serverPort();
        QTest::newRow("jbus_over_tcpip") << map << "com_jbus_tcpip_master" << type_jbus_over_tcpip << true;
    }
    {
        QVariantMap map;
        map["name"] = "com_jbus_master";
        map["type"] = "jbus";
        map["device"] = m_pty.name();
        map["baudrate"] = "9600";
        map["stop"] = "1";
        map["data"] = "8";
        QTest::newRow("jbus") << map << "com_jbus_master" << type_jbus << true;
    }
    {
        QVariantMap map;
        map["name"] = "com_tcpip_master";
        map["type"] = "tcpip";
        map["ip"] = m_tcp.serverAddress().toString();
        map["port"] = m_tcp.serverPort();
        QTest::newRow("tcpip") << map << "com_tcpip_master" << type_tcpip << true;
    }
    {
        QVariantMap map;
        map["name"] = "com_name";
        QTest::newRow("unknown_type") << map << "com_name" << type_com_unknow << false;
    }
    {
        QVariantMap map;
        map["type"] = "jbus";
        QTest::newRow("unknown_name") << map << "Com not named" << type_jbus << false;
    }
}

void JBusTest::testInitialize()
{
    QFETCH(QVariantMap, map);
    QFETCH(QString, name);
    QFETCH(comType, type);
    QFETCH(bool, initialized);

    CComJBus bus(map);
    QCOMPARE(bus.getName(), name);
    QCOMPARE(bus.getType(), type);
#ifndef Q_OS_LINUX
    QEXPECT_FAIL("jbus", "no pseudo tty implementation available on this platform", Abort);
#endif
    QCOMPARE(isInitialized(bus), initialized);
}

void JBusTest::testRtu()
{
    QSKIP("not implemented yet");

    QVariantMap masterConfig;
    masterConfig["name"] = "rtu_master";
    masterConfig["type"] = "jbus";
    masterConfig["device"] = m_pty.name();
    masterConfig["baudrate"] = 9600;
    masterConfig["data"] = 8;
    masterConfig["stop"] = 1;
    CComJBus master(masterConfig);
    QVERIFY(isInitialized(master));

    QVariantMap slaveConfig = masterConfig;
    slaveConfig["name"] = "rtu_slave";
    slaveConfig["slave"] = 1;
    CComJBus slave(slaveConfig);
    QVERIFY(isInitialized(slave));

    const int address = 42;
    CComJBus::BitArray bitsToWrite(32);
    for (int i = 0; i < bitsToWrite.size(); ++i) {
        bitsToWrite[i] = i % 2;
    }
    slave.writeNBitsFunction15(address, bitsToWrite);
    const CComJBus::BitArray bitsRead = master.readNBitsFunction1(address, bitsToWrite.size());
    qDebug() << bitsToWrite << bitsRead;
    QCOMPARE(bitsToWrite, bitsRead);
}

void JBusTest::testTcpip()
{
    uint8_t masterBits[8] = {0, 1, 0, 1, 0, 1, 0, 1};
    const QByteArray ip = QByteArrayLiteral("127.0.0.1");
    const int port = 12346;

    std::promise<bool> startSlave;
    std::thread master([&masterBits, &startSlave, &ip, &port] {
        modbus_t *ctx = modbus_new_tcp(ip.constData(), port);
        if (!ctx) {
            fprintf(stderr, "modbus_new_tcp failed on %s:%d: %s\n",
                    ip.constData(), port, modbus_strerror(errno));
            startSlave.set_value(false);
            return;
        }

        modbus_set_debug(ctx, true);

        int socket = modbus_tcp_listen(ctx, 1);
        if (socket == -1) {
            fprintf(stderr, "modbus_tcp_listen: %s\n", modbus_strerror(errno));
            startSlave.set_value(false);
            return;
        }

        startSlave.set_value(true);
        modbus_tcp_accept(ctx, &socket);

        modbus_mapping_t mapping = {
            sizeof(masterBits), 0, 0, 0,
            masterBits, Q_NULLPTR, Q_NULLPTR, Q_NULLPTR
        };

        for (;;) {
            uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
            int rc = modbus_receive(ctx, query);
            if (rc == -1) {
                fprintf(stderr, "modbus_receive failed: %s\n", modbus_strerror(errno));
                break;
            }

            rc = modbus_reply(ctx, query, rc, &mapping);
            if (rc == -1) {
                fprintf(stderr, "modbus_reply failed: %s\n", modbus_strerror(errno));
                break;
            }
        }

        close(socket);
        modbus_free(ctx);
    });

    // wait until the master is ready to accept connections
    QVERIFY(startSlave.get_future().get());

    {
        QVariantMap slaveConfig;
        slaveConfig["name"] = "rtu_slave";
        slaveConfig["type"] = "tcpip";
        slaveConfig["slave"] = 1;
        slaveConfig["ip"] = ip;
        slaveConfig["port"] = port;
        CComJBus slave(slaveConfig);
        QVERIFY(isInitialized(slave));

        const int address = 0;
        const CComJBus::BitArray bitsRead = slave.readNBitsFunction1(address, sizeof(masterBits));
        QCOMPARE(static_cast<size_t>(bitsRead.size()), sizeof(masterBits));
        CComJBus::BitArray bitsToWrite(bitsRead.size());
        for (uint i = 0; i < sizeof(masterBits); ++i) {
            QCOMPARE(bitsRead[i], masterBits[i]);
            bitsToWrite[i] = !bitsRead[i];
        }
        QVERIFY(bitsToWrite != bitsRead);
        slave.writeNBitsFunction15(address, bitsToWrite);
        QCOMPARE(bitsToWrite, slave.readNBitsFunction1(address, bitsToWrite.size()));
    }
    // destroy the slave to kill the tcpip connection, which stops the master loop as well
    // then we can join the thread
    master.join();
}

QTEST_GUILESS_MAIN(JBusTest)

#include "jbustest.moc"
