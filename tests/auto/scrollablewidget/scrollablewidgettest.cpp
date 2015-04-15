#include <qtest.h>
#include "CScrollableWidget.h"
#include <QLineEdit>
#include <QObject>
class ScrollableWidgetTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

void ScrollableWidgetTest::shouldHaveDefaultValue()
{
    CScrollableWidget w;
    QVERIFY(w.moveDown());
    QVERIFY(w.moveUp());
    QCOMPARE(w.verticalScrollBarPolicy(), Qt::ScrollBarAlwaysOff);
}

QTEST_MAIN(ScrollableWidgetTest)

#include "scrollablewidgettest.moc"

