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

    {
        QVariantMap map;
        map["name"] = "com_jbus_tcp_master";
        map["type"] = "jbus_over_tcpip";
        QTest::newRow("jbus_over_tcpip") << map << "com_jbus_tcp_master" << type_jbus_over_tcpip;
    }
    {
        QVariantMap map;
        map["name"] = "com_jbus_tcp_master";
        map["type"] = "jbus";
        QTest::newRow("jbus") << map << "com_jbus_tcp_master" << type_jbus;
    }
    {
        QVariantMap map;
        map["name"] = "com_jbus_tcp_master";
        QTest::newRow("unknown_type") << map << "com_jbus_tcp_master" << type_com_unknow;
    }
    {
        QVariantMap map;
        map["type"] = "jbus";
        QTest::newRow("unknown_name") << map << "Com not named" << type_jbus;
    }
}

void JBusTest::shouldInitialize()
{
    QFETCH(QVariantMap, map);
    QFETCH(QString, name);
    QFETCH(comType, type);

    CComJBus bus(map);
    QCOMPARE(bus.getName(), name);
    QCOMPARE(bus.getType(), type);
}

QTEST_MAIN(JBusTest)

#include "jbustest.moc"
