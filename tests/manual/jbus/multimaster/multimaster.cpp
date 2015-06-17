#include <QDebug>
#include <QCoreApplication>

#include <CComJBus.h>

#include <unistd.h>

class JBusTest : public QObject
{
public:
    explicit JBusTest(CComJBus *bus1, CComJBus *bus2, CComJBus *bus3, QObject* parent = 0)
        : QObject(parent)
        , m_bus1(bus1)
        , m_bus2(bus2)
        , m_bus3(bus3)
        , m_connected(0)
    {
        connect(bus1, &CComJBus::connected,
                this, &JBusTest::connected);
        connect(bus2, &CComJBus::connected,
                this, &JBusTest::connected);
        connect(bus3, &CComJBus::connected,
                this, &JBusTest::connected);
    }

    struct BusBool
    {
        BusBool(int address, CComJBus::Type type)
            : address(address)
            , type(type)
        {}
        int address;
        CComJBus::Type type;
    };

    void connected(bool success)
    {
        if (!success) {
            qWarning("failed to connect to the I/O board via TCP");
            qApp->exit(1);
            return;
        }
        ++m_connected;
        if (m_connected != 2) {
            return;
        }

//        m_bus1->readInt(0, CComJBus::Input);
//        m_bus2->readInt(1, CComJBus::Output);

        for(int i=0;i<1000;++i){
            m_bus1->writeBool(0x0120, true);
            usleep(200000);
            m_bus2->writeBool(0x0200, true);
            m_bus3->writeBool(0x0200, true);
            usleep(200000);
            m_bus1->writeBool(0x0120, false);
            m_bus2->writeBool(0x0200, false);
            m_bus3->writeBool(0x0200, false);
            usleep(2000000);
        }
        qApp->quit();
    }

private:
    CComJBus *m_bus1;
    CComJBus *m_bus2;
    CComJBus *m_bus3;
    int m_connected;
};

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QVariantMap busConfig;
    busConfig[QStringLiteral("ip")] = QByteArrayLiteral("192.168.1.2");
    busConfig[QStringLiteral("port")] = 502;
    busConfig[QStringLiteral("slave")] = 1;
    busConfig[QStringLiteral("name")] = QStringLiteral("ioboard_tcp");
    busConfig[QStringLiteral("type")] = QStringLiteral("tcpip");
    busConfig[QStringLiteral("debug")] = true;
    CComJBus bus1(busConfig);

     busConfig[QStringLiteral("ip")] = QByteArrayLiteral("192.168.1.12");
    busConfig[QStringLiteral("port")] = 502;
    CComJBus bus2(busConfig);

    busConfig[QStringLiteral("ip")] = QByteArrayLiteral("192.168.1.11");
   busConfig[QStringLiteral("port")] = 502;
   CComJBus bus3(busConfig);

    JBusTest test(&bus1, &bus2, &bus3);

    return app.exec();
}
