#include <qtest.h>
#include "../../../../cot/keyboards/keyboardnormalbutton.h"
#include <QObject>
class KeyboadNormalButtonTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignCharacter();
};




void KeyboadNormalButtonTest::shouldHaveDefaultValue()
{
    KeyboardNormalButton button;
    QVERIFY(button.character().isNull());
}

void KeyboadNormalButtonTest::shouldAssignCharacter()
{
    KeyboardNormalButton button;
    QChar character(QLatin1Char('1'));
    button.setCharacter(character);
    QCOMPARE(button.character(), character);
}

QTEST_MAIN(KeyboadNormalButtonTest)

#include "keyboardnormalbuttontest.moc"
