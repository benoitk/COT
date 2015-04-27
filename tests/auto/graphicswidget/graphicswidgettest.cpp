#include <qtest.h>
#include "CGraphicsWidget.h"
#include "kplotwidget.h"
#include <QObject>
class GraphicsWidgetTest : public QObject
{
    Q_OBJECT
private slots:
    void shouldHaveDefaultValue();
};

void GraphicsWidgetTest::shouldHaveDefaultValue()
{
    CGraphicsWidget w;
    KPlotWidget *plot = w.findChild<KPlotWidget *>(QStringLiteral("plotwidget"));
    QVERIFY(plot);
}

QTEST_MAIN(GraphicsWidgetTest)

#include "graphicswidgettest.moc"
