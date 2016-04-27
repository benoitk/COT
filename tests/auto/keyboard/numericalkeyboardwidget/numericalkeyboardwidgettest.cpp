#include <qtest.h>
#include "CNumericalKeyboardWidget.h"
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
class NumericalKeyboardWidgetTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void shouldHaveDefaultValue();
    void shouldLimitToFloatPrecision();
};

void NumericalKeyboardWidgetTest::initTestCase()
{
    QLocale::setDefault(QLocale::C);
}

void NumericalKeyboardWidgetTest::shouldHaveDefaultValue()
{
    CNumericalKeyboardWidget w;
    QLineEdit *lineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(lineEdit);
}


void NumericalKeyboardWidgetTest::shouldLimitToFloatPrecision()
{
    CNumericalKeyboardWidget w;
    w.setFloatNumber(3333.3,1);
    QCOMPARE(QString::number(w.floatNumber(), 'g', 7), QString("3333.3"));
    QPushButton *button3 = 0;
    foreach(QPushButton *button, w.findChildren<QPushButton *>()) {
        if (button->text() == QLatin1String("3")) {
            button3 = button;
            break;
        }
    }
    QLineEdit *lineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(lineEdit);
    button3->click();
    QCOMPARE(QString::number(w.floatNumber(), 'g', 7), QString("3333.33"));
    QCOMPARE(lineEdit->text(), QString("3,333.33"));
    button3->click();
    QCOMPARE(QString::number(w.floatNumber(), 'g', 7), QString("3333.333"));
    QCOMPARE(lineEdit->text(), QString("3,333.333"));

    // Another testcase from the bug report
    w.setFloatNumber(3333333,0);
    QCOMPARE(lineEdit->text(), QString("3,333,333"));
    QCOMPARE(QString::number(w.floatNumber(), 'f', 0), QString("3333333"));
    button3->click();
    QCOMPARE(lineEdit->text(), QString("3,333,333")); // no change
    QCOMPARE(QString::number(w.floatNumber(), 'f', 0), QString("3333333")); // no change
}


QTEST_MAIN(NumericalKeyboardWidgetTest)

#include "numericalkeyboardwidgettest.moc"
