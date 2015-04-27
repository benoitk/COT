#include <qtest.h>
#include <QObject>
class GraphicsWidgetTest : public QObject
{
    Q_OBJECT
private slots:
    void shouldHaveDefaultValue();
};

void GraphicsWidgetTest::shouldHaveDefaultValue()
{
}

QTEST_MAIN(GraphicsWidgetTest)

#include "graphicswidgettest.moc"
