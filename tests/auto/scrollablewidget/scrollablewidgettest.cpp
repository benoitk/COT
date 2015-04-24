#include <qtest.h>
#include "CScrollableWidget.h"
#include <QLineEdit>
#include <QObject>
#include <QAction>
class ScrollableWidgetTest : public QObject
{
    Q_OBJECT
private slots:
    void shouldHaveDefaultValue();
};

void ScrollableWidgetTest::shouldHaveDefaultValue()
{
    CScrollableWidget w;
    QVERIFY(w.moveDown());
    QVERIFY(w.moveUp());
    QCOMPARE(w.verticalScrollBarPolicy(), Qt::ScrollBarAlwaysOff);
    QVERIFY(!w.moveUp()->isEnabled());
    QVERIFY(!w.moveDown()->isEnabled());
    QVERIFY(w.moveDown()->autoRepeat());
    QVERIFY(w.moveUp()->autoRepeat());
}

QTEST_MAIN(ScrollableWidgetTest)

#include "scrollablewidgettest.moc"

