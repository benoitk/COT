#include <qtest.h>
#include <qtestmouse.h>
#include <QSignalSpy>
#include "CKeyboardNormalButton.h"
#include <QObject>
class KeyboadNormalButtonTest : public QObject
{
    Q_OBJECT
private slots:
    void shouldHaveDefaultValue();
    void shouldAssignCharacter();
    void shouldEmitPressSignal();
    void shouldEmitClickSignal();
    void shouldEmitReleasedSignal();
};




void KeyboadNormalButtonTest::shouldHaveDefaultValue()
{
    CKeyboardNormalButton button;
    QVERIFY(button.character().isNull());
}

void KeyboadNormalButtonTest::shouldAssignCharacter()
{
    CKeyboardNormalButton button;
    QChar character(QLatin1Char('1'));
    button.setCharacter(character);
    QCOMPARE(button.character(), character);

    character = QLatin1Char('2');
    button.setCharacter(character);
    QCOMPARE(button.character(), character);
}

void KeyboadNormalButtonTest::shouldEmitPressSignal()
{
    CKeyboardNormalButton button;
    //We don't have default character.
    QSignalSpy spy(&button, SIGNAL(pressed(QChar)));
    QTest::mousePress(&button, Qt::LeftButton);
    QCOMPARE(spy.count(), 0);

    button.setCharacter(QLatin1Char('1'));
    QTest::mousePress(&button, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<QChar>(), QChar(QLatin1Char('1')));
}

void KeyboadNormalButtonTest::shouldEmitClickSignal()
{
    CKeyboardNormalButton button;
    //We don't have default character.
    QSignalSpy spy(&button, SIGNAL(clicked(QChar)));
    QTest::mouseClick(&button, Qt::LeftButton);
    QCOMPARE(spy.count(), 0);

    button.setCharacter(QLatin1Char('1'));
    QTest::mouseClick(&button, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<QChar>(), QChar(QLatin1Char('1')));
}

void KeyboadNormalButtonTest::shouldEmitReleasedSignal()
{
    //FIXME
    /*
    CKeyboardNormalButton button;
    //We don't have default character.
    QSignalSpy spy(&button, SIGNAL(released(QChar)));
    QTest::mouseRelease(&button, Qt::LeftButton);
    QCOMPARE(spy.count(), 0);

    button.setCharacter(QLatin1Char('1'));
    QTest::mouseRelease(&button, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<QChar>(), QChar(QLatin1Char('1')));
    */
}

QTEST_MAIN(KeyboadNormalButtonTest)

#include "keyboardnormalbuttontest.moc"
