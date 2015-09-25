#include <qtest.h>

#include <QObject>
#include "CComJBus.h"

#include <QDebug>
#include <QTcpServer>
#include <QHostAddress>
#include <QBitArray>
#include <QSignalSpy>

#include <thread>
#include <future>

#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
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
    void testInvalidSlave();

private:
    bool waitForInitialization(const CComJBus &bus, int timeoutMs = 500) const
    {
        QSignalSpy spy(&bus, SIGNAL(connected(bool)));
        spy.wait(timeoutMs);
        return spy.isValid() && spy.size() == 1 && spy.first().size() == 1 && spy.first().first().toBool();
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
    QTest::addColumn<enumComType>("type");
    QTest::addColumn<bool>("initialized");

    {
        QVariantMap map;
        map["name"] = "com_jbus_tcpip_master";
        map["type"] = "jbus_over_tcpip";
        map["ip"] = m_tcp.serverAddress().toString();
        map["port"] = m_tcp.serverPort();
        map["debug"] = true;
        QTest::newRow("jbus_over_tcpip") << map << "com_jbus_tcpip_master" << e_type_jbus_over_tcpip << true;
    }
    {
        QVariantMap map;
        map["name"] = "com_jbus_master";
        map["type"] = "jbus";
        map["device"] = m_pty.name();
        map["baudrate"] = "9600";
        map["stop"] = "1";
        map["data"] = "8";
        map["debug"] = true;
        QTest::newRow("jbus") << map << "com_jbus_master" << e_type_jbus << true;
    }
    {
        QVariantMap map;
        map["name"] = "com_tcpip_master";
        map["type"] = "tcpip";
        map["ip"] = m_tcp.serverAddress().toString();
        map["port"] = m_tcp.serverPort();
        map["debug"] = true;
        QTest::newRow("tcpip") << map << "com_tcpip_master" << e_type_tcpip << true;
    }
    {
        QVariantMap map;
        map["name"] = "com_name";
        map["debug"] = true;
        QTest::newRow("unknown_type") << map << "com_name" << e_type_com_unknow << false;
    }
    {
        QVariantMap map;
        map["type"] = "jbus";
        map["debug"] = true;
        QTest::newRow("unknown_name") << map << "Com not named" << e_type_jbus << false;
    }
}

void JBusTest::testInitialize()
{
    QFETCH(QVariantMap, map);
    QFETCH(QString, name);
    QFETCH(enumComType, type);
    QFETCH(bool, initialized);

    CComJBus bus(map);
    QCOMPARE(bus.getName(), name);
    QCOMPARE(bus.getType(), type);
#ifndef Q_OS_LINUX
    QEXPECT_FAIL("jbus", "no pseudo tty implementation available on this platform", Abort);
#endif
    QCOMPARE(waitForInitialization(bus), initialized);
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
        config["debug"] = true;
        QTest::newRow("tcpip") << config;
    }
    {
        QVariantMap config;
        config["name"] = "rtutcpip_slave";
        config["type"] = "jbus_over_tcpip";
        config["slave"] = 255;
        config["ip"] = "127.0.0.1";
        config["port"] = 12346;
        config["debug"] = true;
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
        config["debug"] = true;
        // FIXME: the pty does not work properly, and the test fails
//         QTest::newRow("jbus") << config;
    }
}

void JBusTest::testSlave()
{
    CComJBus::BitArray masterBits = CComJBus::BitArray()
        << 0 << 1 << 0 << 1 << 0 << 1 << 0 << 1;
    CComJBus::BitArray masterInputBits = CComJBus::BitArray()
        << 1 << 1 << 0 << 0;
    CComJBus::WordArray masterInputWords = CComJBus::WordArray()
        << 4 << 3 << 2 << 1 << 0;
    CComJBus::WordArray masterWords = CComJBus::WordArray()
        << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7;

    std::promise<bool> startSlave;

    QFETCH(QVariantMap, config);

    std::thread master([&masterBits, &masterInputBits, &masterInputWords, &masterWords,
                        &startSlave, &config]
    {
        std::unique_ptr<modbus_t, void(*)(modbus_t*)> ctx(Q_NULLPTR, [] (modbus_t *ctx) {
            if (ctx) {
                modbus_close(ctx);
                modbus_free(ctx);
            }
        });
        int socket = -1;

        const enumComType type = stringToComType(config["type"].toString());
        switch (type)
        {
        case e_type_jbus_over_tcpip:
        case e_type_tcpip:
            {
                const QByteArray ip = config["ip"].toByteArray();
                const int port = config["port"].toInt();

                if (type == e_type_tcpip)
                    ctx.reset(modbus_new_tcp(ip.constData(), port));
                else
                    ctx.reset(modbus_new_rtutcp(ip.constData(), port));

                if (!ctx) {
                    fprintf(stderr, "%s failed on %s:%d: %s\n",
                            (type == e_type_tcpip ? "modbus_new_tcp" : "modbus_new_rtutcp"),
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
        case e_type_jbus:
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
        case e_type_com_unknow:
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
        if (type == e_type_jbus) {
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
            masterBits.size(), masterInputBits.size(), masterInputWords.size(), masterWords.size(),
            masterBits.data(), masterInputBits.data(), masterInputWords.data(), masterWords.data()
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
        QVERIFY(waitForInitialization(slave));

        qDebug() << "testing readNBits / writeNBits";
        const int address = 0;
        const CComJBus::BitArray bitsRead = slave.readNBitsFunction1(address, masterBits.size());
        QCOMPARE(bitsRead.size(), masterBits.size());
        CComJBus::BitArray bitsToWrite(bitsRead.size());
        QCOMPARE(bitsRead, masterBits);
        for (int i = 0; i < masterBits.size(); ++i) {
            bitsToWrite[i] = !bitsRead[i];
        }
        QVERIFY(bitsToWrite != bitsRead);
        slave.writeNBitsFunction15(address, bitsToWrite);
        QCOMPARE(bitsToWrite, slave.readNBitsFunction1(address, bitsToWrite.size()));

        qDebug() << "testing readNWords / writeNWords";
        const CComJBus::WordArray wordsRead = slave.readNWordsFunction3(address, masterWords.size());
        QCOMPARE(wordsRead.size(), masterWords.size());
        CComJBus::WordArray wordsToWrite(wordsRead.size());
        QCOMPARE(wordsRead, masterWords);
        for (int i = 0; i < masterWords.size(); ++i) {
            QCOMPARE(wordsRead[i], masterWords[i]);
            wordsToWrite[i] = wordsRead[i] + 1;
        }
        QVERIFY(wordsToWrite != wordsRead);
        slave.writeNWordsFunction16(address, wordsToWrite);
        QCOMPARE(wordsToWrite, slave.readNWordsFunction3(address, wordsToWrite.size()));

        qDebug() << "testing readNInputBits";
        const CComJBus::BitArray inputBitsRead = slave.readNInputBitsFunction2(0, masterInputBits.size());
        QCOMPARE(inputBitsRead, masterInputBits);

        qDebug() << "testing readNInputWords";
        const CComJBus::WordArray inputWordsRead = slave.readNInputWordsFunction4(0, masterInputWords.size());
        QCOMPARE(inputWordsRead, masterInputWords);

        qDebug() << "testing writeBit";
        const CComJBus::BitArray oldBits = masterBits;
        for (int i = 0; i < oldBits.size(); ++i) {
            slave.writeBitFunction5(i, !oldBits[i]);
            QCOMPARE(static_cast<bool>(masterBits[i]), !oldBits[i]);
        }

        qDebug() << "testing writeWord";
        const CComJBus::WordArray oldWords = masterWords;
        for (int i = 0; i < oldWords.size(); ++i) {
            slave.writeWordFunction6(i, oldWords[i] + 42);
            QCOMPARE(static_cast<int>(masterWords[i]), oldWords[i] + 42);
        }

        qDebug() << "testing readBool/writeBool";
        masterBits[0] = true;
        const bool b = slave.readBool(0, CComJBus::Output);
        QCOMPARE(b, true);
        slave.writeBool(0, !b);
        QCOMPARE(slave.readBool(0, CComJBus::Output), !b);

        qDebug() << "testing readInt/writeInt";
        const int intData = 42;
        memcpy(masterWords.data() + 2, &intData, sizeof(intData));
        const int i = slave.readInt(2, CComJBus::Output);
        QCOMPARE(i, intData);
        slave.writeInt(2, 24);
        QCOMPARE(slave.readInt(2, CComJBus::Output), 24);

        qDebug() << "testing readFloat/writeFloat";
        const float floatData = 2.5;
        const int floatAddress = 4;
        memcpy(masterWords.data() + floatAddress, &floatData, sizeof(floatData));
        const float f = slave.readFloat(floatAddress, CComJBus::Output);
        QCOMPARE(f, floatData);
        slave.writeFloat(floatAddress, 4.5);
        QCOMPARE(slave.readFloat(floatAddress, CComJBus::Output), 4.5);
    }
    // destroy the slave to kill the tcpip connection, which stops the master loop as well
    // then we can join the thread
    master.join();
}

void JBusTest::testInvalidSlave()
{
    // don't crash
    CComJBus bus({});
    bus.readBool(0, CComJBus::Input);
    bus.readBool(0, CComJBus::Output);
    bus.writeBool(0, true);
    bus.readInt(0, CComJBus::Input);
    bus.readInt(0, CComJBus::Output);
    bus.writeInt(0, 1);
    bus.readFloat(0, CComJBus::Input);
    bus.readFloat(0, CComJBus::Output);
    bus.writeFloat(0, 42.0);
}

QTEST_GUILESS_MAIN(JBusTest)

#include "jbustest.moc"
