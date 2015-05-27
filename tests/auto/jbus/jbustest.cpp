#include <qtest.h>

#include <QObject>
#include "CComJBus.h"

#include <QDebug>
#include <QTcpServer>
#include <QHostAddress>
#include <QBitArray>

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

QTEST_GUILESS_MAIN(JBusTest)

#include "jbustest.moc"
