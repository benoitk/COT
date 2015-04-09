#ifndef KEYBOARDSPECIALBUTTON_H
#define KEYBOARDSPECIALBUTTON_H

#include "keyboardbuttonbase.h"

class KeyboardSpecialButton : public KeyboardButtonBase
{
    Q_OBJECT
public:
    explicit KeyboardSpecialButton(QWidget *parent = Q_NULLPTR);
    ~KeyboardSpecialButton();

    Qt::Key specialKey() const;
    void setSpecialKey(const Qt::Key &specialKey);

private Q_SLOTS:
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
