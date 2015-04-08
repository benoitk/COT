#ifndef KEYBOARDNORMALBUTTON_H
#define KEYBOARDNORMALBUTTON_H

#include "keyboardbuttonbase.h"

class KeyboardNormalButton : public KeyboardButtonBase
{
    Q_OBJECT
public:
    explicit KeyboardNormalButton(QWidget *parent = Q_NULLPTR);
    ~KeyboardNormalButton();


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
    QChar mCharacter;
};

#endif // KEYBOARDNORMALBUTTON_H
