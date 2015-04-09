#include "keyboardspecialbutton.h"

KeyboardSpecialButton::KeyboardSpecialButton(QWidget *parent)
    : KeyboardButtonBase(parent),
      m_specialKey(Qt::Key_Any)
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
    if (m_specialKey != Qt::Key_Any) {
       Q_EMIT pressed(m_specialKey);
    }
}

void KeyboardSpecialButton::slotButtonReleased()
{
    if (m_specialKey != Qt::Key_Any) {
        Q_EMIT released(m_specialKey);
    }
}

void KeyboardSpecialButton::slotButtonClicked()
{
    if (m_specialKey != Qt::Key_Any) {
        Q_EMIT clicked(m_specialKey);
    }
}

Qt::Key KeyboardSpecialButton::specialKey() const
{
    return m_specialKey;
}

void KeyboardSpecialButton::setSpecialKey(const Qt::Key &specialKey)
{
    m_specialKey = specialKey;
}

