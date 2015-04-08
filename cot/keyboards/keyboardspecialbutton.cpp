#include "keyboardspecialbutton.h"

KeyboardSpecialButton::KeyboardSpecialButton(QWidget *parent)
    : KeyboardButtonBase(parent),
      mSpecialKey(Qt::Key_Any)
{
    connect( this, &QAbstractButton::pressed, this, &KeyboardSpecialButton::slotButtonPressed );
    connect( this, &QAbstractButton::released, this, &KeyboardSpecialButton::slotButtonReleased );
    connect( this, &QAbstractButton::clicked, this, &KeyboardSpecialButton::slotButtonClicked );
}

KeyboardSpecialButton::~KeyboardSpecialButton()
{

}

void KeyboardSpecialButton::slotButtonPressed()
{
    if (mSpecialKey != Qt::Key_Any) {
       Q_EMIT pressed(mSpecialKey);
    }
}

void KeyboardSpecialButton::slotButtonReleased()
{
    if (mSpecialKey != Qt::Key_Any) {
        Q_EMIT released(mSpecialKey);
    }
}

void KeyboardSpecialButton::slotButtonClicked()
{
    if (mSpecialKey != Qt::Key_Any) {
        Q_EMIT clicked(mSpecialKey);
    }
}

Qt::Key KeyboardSpecialButton::specialKey() const
{
    return mSpecialKey;
}

void KeyboardSpecialButton::setSpecialKey(const Qt::Key &specialKey)
{
    mSpecialKey = specialKey;
}

