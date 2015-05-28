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

    void testSlave_data();
    void testSlave();

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

void JBusTest::testSlave_data()
{
    QTest::addColumn<QVariantMap>("config");

    {
        QVariantMap config;
        config["name"] = "tcpip_slave";
        config["type"] = "tcpip";
        config["slave"] = 255;
        config["ip"] = "127.0.0.1";
        config["port"] = 12346;
        QTest::newRow("tcpip") << config;
    }
    {
        QVariantMap config;
        config["name"] = "rtutcpip_slave";
        config["type"] = "jbus_over_tcpip";
        config["slave"] = 255;
        config["ip"] = "127.0.0.1";
        config["port"] = 12346;
        QTest::newRow("jbus_over_tcpip") << config;
    }
    {
        QVariantMap config;
        config["name"] = "jbus_slave";
        config["type"] = "jbus";
        config["device"] = m_pty.name();
        config["baudrate"] = "9600";
        config["stop"] = "1";
        config["data"] = "8";
        config["slave"] = 1;
        // FIXME: the pty does not work properly, and the test fails
//         QTest::newRow("jbus") << config;
    }
}

void JBusTest::testSlave()
{
    uint8_t masterBits[8] = {0, 1, 0, 1, 0, 1, 0, 1};

    std::promise<bool> startSlave;
    std::promise<bool> stopMaster;

    QFETCH(QVariantMap, config);

    std::thread master([&masterBits, &startSlave, &stopMaster, &config] {
        std::unique_ptr<modbus_t, void(*)(modbus_t*)> ctx(Q_NULLPTR, [] (modbus_t *ctx) {
            if (ctx) {
                modbus_close(ctx);
                modbus_free(ctx);
            }
        });
        int socket = -1;

        const comType type = stringToComType(config["type"].toString());
        switch (type)
        {
        case type_jbus_over_tcpip:
        case type_tcpip:
            {
                const QByteArray ip = config["ip"].toByteArray();
                const int port = config["port"].toInt();

                if (type == type_tcpip)
                    ctx.reset(modbus_new_tcp(ip.constData(), port));
                else
                    ctx.reset(modbus_new_rtutcp(ip.constData(), port));

                if (!ctx) {
                    fprintf(stderr, "%s failed on %s:%d: %s\n",
                            (type == type_tcpip ? "modbus_new_tcp" : "modbus_new_rtutcp"),
                            ip.constData(), port, modbus_strerror(errno));
                }

                socket = modbus_tcp_listen(ctx.get(), 1);
                if (socket == -1) {
                    fprintf(stderr, "modbus_tcp_listen failed: %s\n", modbus_strerror(errno));
                    startSlave.set_value(false);
                    return;
                }

                break;
            }
        case type_jbus:
            {
                const QByteArray device = config["device"].toByteArray();
                const int baudrate = config["baudrate"].toInt();
                const int data = config["data"].toInt();
                const int stop = config["stop"].toInt();
                ctx.reset(modbus_new_rtu(device.constData(), baudrate, 'N', data, stop));
                if (!ctx) {
                    fprintf(stderr, "modbus_new_rtu failed on %s (baud=%d, data=%d, stop=%d): %s\n",
                            device.constData(), baudrate, data, stop, modbus_strerror(errno));
                }
                break;
            }
            break;
        case type_com_unknow:
            fprintf(stderr, "unhandled com type: %s\n",
                    qPrintable(config["type"].toString()));
            break;
        }

        if (!ctx) {
            startSlave.set_value(false);
            return;
        }

        modbus_set_debug(ctx.get(), true);

        startSlave.set_value(true);
        if (type == type_jbus) {
            if (modbus_connect(ctx.get()) == -1) {
                fprintf(stderr, "Unable to connect %s\n", modbus_strerror(errno));
                return;
            }
        } else {
            if (modbus_tcp_accept(ctx.get(), &socket) == -1) {
                fprintf(stderr, "modbus_tcp_accept failed: %s\n", modbus_strerror(errno));
                return;
            }
        }

        modbus_mapping_t mapping = {
            sizeof(masterBits), 0, 0, 0,
            masterBits, Q_NULLPTR, Q_NULLPTR, Q_NULLPTR
        };

        for (;;) {
            uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
            int rc = modbus_receive(ctx.get(), query);
            if (rc == -1) {
                fprintf(stderr, "modbus_receive failed: %s\n", modbus_strerror(errno));
                break;
            }

            rc = modbus_reply(ctx.get(), query, rc, &mapping);
            if (rc == -1) {
                fprintf(stderr, "modbus_reply failed: %s\n", modbus_strerror(errno));
                break;
            }
        }

        close(socket);
    });

    // wait until the master is ready to accept connections
    QVERIFY(startSlave.get_future().get());

    {
        CComJBus slave(config);
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
