#ifndef KEYBOARDBUTTONBASE_H
#define KEYBOARDBUTTONBASE_H

#include <QPushButton>

class CKeyboardButtonBase : public QPushButton
{
    Q_OBJECT
public:
    explicit CKeyboardButtonBase(QWidget *parent = Q_NULLPTR);
    ~CKeyboardButtonBase();
};

#endif // KEYBOARDBUTTONBASE_H
