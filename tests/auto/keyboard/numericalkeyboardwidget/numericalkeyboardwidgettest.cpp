#include <qtest.h>
#include "CNumericalKeyboardWidget.h"
#include <QLineEdit>
#include <QObject>
class NumericalKeyboardWidgetTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

void NumericalKeyboardWidgetTest::shouldHaveDefaultValue()
{
    CNumericalKeyboardWidget w;
    QLineEdit *lineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(lineEdit);
}

QTEST_MAIN(NumericalKeyboardWidgetTest)

#include "numericalkeyboardwidgettest.moc"
