#include "CKeyboardNormalButton.h"
#include <QDebug>

CKeyboardNormalButton::CKeyboardNormalButton(QWidget *parent)
    : CKeyboardButtonBase(parent)
{
    connect( this, &QAbstractButton::pressed, this, &CKeyboardNormalButton::slotButtonPressed );
    connect( this, &QAbstractButton::released, this, &CKeyboardNormalButton::slotButtonReleased );
    connect( this, &QAbstractButton::clicked, this, &CKeyboardNormalButton::slotButtonClicked );
}

CKeyboardNormalButton::~CKeyboardNormalButton()
{

}

QChar CKeyboardNormalButton::character() const
{
    return m_character;
}

void CKeyboardNormalButton::setCharacter(const QChar &character)
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

void CKeyboardNormalButton::slotButtonPressed()
{
    if (!m_character.isNull()) {
       Q_EMIT pressed(m_character);
    }
}

void CKeyboardNormalButton::slotButtonReleased()
{
    if (!m_character.isNull()) {
        Q_EMIT released(m_character);
    }
}

void CKeyboardNormalButton::slotButtonClicked()
{
    if (!m_character.isNull()) {
        Q_EMIT clicked(m_character);
    }
}

