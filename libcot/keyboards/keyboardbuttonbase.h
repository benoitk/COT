#ifndef KEYBOARDBUTTONBASE_H
#define KEYBOARDBUTTONBASE_H

#include <QPushButton>

class KeyboardButtonBase : public QPushButton
{
    Q_OBJECT
public:
    explicit KeyboardButtonBase(QWidget *parent = Q_NULLPTR);
    ~KeyboardButtonBase();
};

#endif // KEYBOARDBUTTONBASE_H
