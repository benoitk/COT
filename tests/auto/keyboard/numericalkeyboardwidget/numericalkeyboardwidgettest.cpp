#include <qtest.h>
#include "numericalkeyboardwidget.h"
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
    NumericalKeyboardWidget w;
    QLineEdit *lineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(lineEdit);
}

QTEST_MAIN(NumericalKeyboardWidgetTest)

#include "numericalkeyboardwidgettest.moc"
