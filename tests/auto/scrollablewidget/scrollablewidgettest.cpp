#include <qtest.h>
//#include ".h"
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
}

QTEST_MAIN(ScrollableWidgetTest)

#include "scrollablewidgettest.moc"

