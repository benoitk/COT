#ifndef KEYBOARDNORMALBUTTON_H
#define KEYBOARDNORMALBUTTON_H

#include "CKeyboardButtonBase.h"
#include "../../libcot/cot_global.h"

class COTWIDGETS_EXPORT CKeyboardNormalButton : public CKeyboardButtonBase
{
    Q_OBJECT
public:
    explicit CKeyboardNormalButton(QWidget *parent = Q_NULLPTR);
    ~CKeyboardNormalButton();


    QChar character() const;
    void setCharacter(const QChar &character);

Q_SIGNALS:
    void pressed(QChar);
    void released(QChar);
    void clicked(QChar);

private Q_SLOTS:
    void slotButtonPressed();
    void slotButtonReleased();
    void slotButtonClicked();

private:
    QChar m_character;
};

#endif // KEYBOARDNORMALBUTTON_H