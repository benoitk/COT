#include <qtest.h>
#include "../../../../cot/keyboards/keyboardwidget.h"
#include <QLineEdit>
#include <QObject>
class KeyboadWidgetTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

void KeyboadWidgetTest::shouldHaveDefaultValue()
{
    KeyboardWidget w;
    QLineEdit *lineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(lineEdit);
    QVERIFY(lineEdit->isReadOnly());
}

QTEST_MAIN(KeyboadWidgetTest)

#include "keyboardwidgettest.moc"
