#ifndef KEYBOARDSPECIALBUTTON_H
#define KEYBOARDSPECIALBUTTON_H

#include "CKeyboardButtonBase.h"

class CKeyboardSpecialButton : public CKeyboardButtonBase
{
    Q_OBJECT
public:
    explicit CKeyboardSpecialButton(CKeyboardButtonBase::Type type = CKeyboardButtonBase::Undefined, QWidget *parent = Q_NULLPTR);
    ~CKeyboardSpecialButton();

    Qt::Key specialKey() const;
    void setSpecialKey(const Qt::Key &specialKey);

private slots:
    void slotButtonPressed();
    void slotButtonReleased();
    void slotButtonClicked();

Q_SIGNALS:
    void pressed(Qt::Key);
    void released(Qt::Key);
    void clicked(Qt::Key);

private:
    Qt::Key m_specialKey;
};

#endif // KEYBOARDSPECIALBUTTON_H
