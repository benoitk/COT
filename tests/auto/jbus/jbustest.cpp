#include <qtest.h>

#include <QObject>
#include "CComJBus.h"

#include <QDebug>
#include <QTcpServer>
#include <QHostAddress>

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
    void shouldInitialize_data();
    void shouldInitialize();

private:
    PseudoTerminal m_pty;
    QTcpServer m_tcp;
};

void JBusTest::initTestCase()
{
    m_pty.init();
    QVERIFY(m_tcp.listen(QHostAddress::LocalHost, 12345));
}

void JBusTest::shouldInitialize_data()
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

void JBusTest::shouldInitialize()
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
    QCOMPARE(bus.initialized(), initialized);
}

QTEST_GUILESS_MAIN(JBusTest)

#include "jbustest.moc"
