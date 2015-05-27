#include <qtest.h>

#include <QObject>
#include "CComJBus.h"

class JBusTest : public QObject
{
    Q_OBJECT
private slots:
    void shouldInitialize_data();
    void shouldInitialize();
};

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
        map["ip"] = "127.0.0.1";
        map["port"] = "12345";
        QTest::newRow("jbus_over_tcpip") << map << "com_jbus_tcpip_master" << type_jbus_over_tcpip << true;
    }
    {
        QVariantMap map;
        map["name"] = "com_jbus_master";
        map["type"] = "jbus";
        map["device"] = "/dev/ttyS0";
        map["baudrate"] = "9600";
        map["stop"] = "1";
        map["data"] = "8";
        QTest::newRow("jbus") << map << "com_jbus_master" << type_jbus << true;
    }
    {
        QVariantMap map;
        map["name"] = "com_tcpip_master";
        map["type"] = "tcpip";
        map["ip"] = "127.0.0.1";
        map["port"] = "12345";
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
    QEXPECT_FAIL("jbus", "connection to the ttyS0 device fails, need to use a pseudo tty", Abort);
    QCOMPARE(bus.initialized(), initialized);
}

QTEST_GUILESS_MAIN(JBusTest)

#include "jbustest.moc"
