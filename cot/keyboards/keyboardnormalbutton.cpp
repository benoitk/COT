#include "keyboardnormalbutton.h"

KeyboardNormalButton::KeyboardNormalButton(QWidget *parent)
    : KeyboardButtonBase(parent)
{
    connect( this, &QAbstractButton::pressed, this, &KeyboardNormalButton::slotButtonPressed );
    connect( this, &QAbstractButton::released, this, &KeyboardNormalButton::slotButtonReleased );
    connect( this, &QAbstractButton::clicked, this, &KeyboardNormalButton::slotButtonClicked );
}

KeyboardNormalButton::~KeyboardNormalButton()
{

}

QChar KeyboardNormalButton::character() const
{
    return mCharacter;
}

void KeyboardNormalButton::setCharacter(const QChar &character)
{
    if (mCharacter != character) {
        mCharacter = character;
        setText(mCharacter);
    }
}

void KeyboardNormalButton::slotButtonPressed()
{
    if (!mCharacter.isNull()) {
       Q_EMIT pressed(mCharacter);
    }
}

void KeyboardNormalButton::slotButtonReleased()
{
    if (!mCharacter.isNull()) {
        Q_EMIT released(mCharacter);
    }
}

void KeyboardNormalButton::slotButtonClicked()
{
    if (!mCharacter.isNull()) {
        Q_EMIT clicked(mCharacter);
    }
}

