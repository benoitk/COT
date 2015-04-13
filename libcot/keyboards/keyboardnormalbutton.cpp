#include "keyboardnormalbutton.h"
#include <QDebug>

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
    return m_character;
}

void KeyboardNormalButton::setCharacter(const QChar &character)
{
    if (m_character != character) {
        m_character = character;
        if (m_character == QLatin1Char('&')) {
            setText(QLatin1String("&&"));
        } else {
            setText(m_character);
        }
    }
}

void KeyboardNormalButton::slotButtonPressed()
{
    if (!m_character.isNull()) {
       Q_EMIT pressed(m_character);
    }
}

void KeyboardNormalButton::slotButtonReleased()
{
    if (!m_character.isNull()) {
        Q_EMIT released(m_character);
    }
}

void KeyboardNormalButton::slotButtonClicked()
{
    if (!m_character.isNull()) {
        Q_EMIT clicked(m_character);
    }
}

