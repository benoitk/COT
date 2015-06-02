#include <QDebug>
#include <QCoreApplication>

#include <CComJBus.h>

#include <unistd.h>

class JBusTest : public QObject
{
public:
    explicit JBusTest(CComJBus *bus, QObject* parent = 0)
        : QObject(parent)
        , m_bus(bus)
    {}

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

        { // digital input bits
            check(BusBool(0x0100, CComJBus::Input));
            check(BusBool(0x0101, CComJBus::Input));
        }

        { // digital output bits
            check(BusBool(0x0200, CComJBus::Output));
            check(BusBool(0x0201, CComJBus::Output));
            check(BusBool(0x0202, CComJBus::Output));
            check(BusBool(0x0203, CComJBus::Output));
        }

        { // voltage output
            check(BusBool(0x0300, CComJBus::Output));
            check(BusBool(0x0301, CComJBus::Output));
        }

        { // loop
            qDebug() << "loop value at 0x0400:" << m_bus->readInt(0x0400, CComJBus::Output);
        }
        qApp->quit();
    }

private:
    void check(const BusBool& bit)
    {
        qDebug().nospace() << "reading " << (bit.type == CComJBus::Input ? "input" : "output") << " bit at address 0x" << hex << bit.address;
        const bool value = m_bus->readBool(bit.address, bit.type);
        qDebug() << "result =" << value;
        if (bit.type == CComJBus::Output) {
            qDebug() << "writing negated value";
            m_bus->writeBool(bit.address, !value);
            const bool newValue = m_bus->readBool(bit.address, bit.type);
            usleep(20000);
            qDebug() << "new value is " << newValue;
            Q_ASSERT(newValue != value);
            qDebug() << "resetting value";
            m_bus->writeBool(bit.address, value);
        }
    }

    CComJBus *m_bus;
};

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QVariantMap busConfig;
    busConfig[QStringLiteral("ip")] = QByteArrayLiteral("192.168.1.10");
    busConfig[QStringLiteral("port")] = 502;
    busConfig[QStringLiteral("slave")] = 1;
    busConfig[QStringLiteral("name")] = QStringLiteral("ioboard_tcp");
    busConfig[QStringLiteral("type")] = QStringLiteral("tcpip");
    busConfig[QStringLiteral("debug")] = true;
    CComJBus bus(busConfig);

    JBusTest test(&bus);
    QObject::connect(&bus, &CComJBus::connected,
                     &test, &JBusTest::connected);

    return app.exec();
}
