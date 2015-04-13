#include "CKeyboardSpecialButton.h"

CKeyboardSpecialButton::CKeyboardSpecialButton(QWidget *parent)
    : CKeyboardButtonBase(parent),
      m_specialKey(Qt::Key_Any)
{
    connect( this, &QAbstractButton::pressed, this, &CKeyboardSpecialButton::slotButtonPressed );
    connect( this, &QAbstractButton::released, this, &CKeyboardSpecialButton::slotButtonReleased );
    connect( this, &QAbstractButton::clicked, this, &CKeyboardSpecialButton::slotButtonClicked );
}

CKeyboardSpecialButton::~CKeyboardSpecialButton()
{

}

void CKeyboardSpecialButton::slotButtonPressed()
{
    if (m_specialKey != Qt::Key_Any) {
       Q_EMIT pressed(m_specialKey);
    }
}

void CKeyboardSpecialButton::slotButtonReleased()
{
    if (m_specialKey != Qt::Key_Any) {
        Q_EMIT released(m_specialKey);
    }
}

void CKeyboardSpecialButton::slotButtonClicked()
{
    if (m_specialKey != Qt::Key_Any) {
        Q_EMIT clicked(m_specialKey);
    }
}

Qt::Key CKeyboardSpecialButton::specialKey() const
{
    return m_specialKey;
}

void CKeyboardSpecialButton::setSpecialKey(const Qt::Key &specialKey)
{
    m_specialKey = specialKey;
}

