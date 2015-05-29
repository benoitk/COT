#ifndef KEYBOARDBUTTONBASE_H
#define KEYBOARDBUTTONBASE_H

#include <QPushButton>

class CKeyboardButtonBase : public QPushButton
{
    Q_OBJECT
public:
    enum Type {
        Undefined,
        Alpha,
        Numeric
    };

    explicit CKeyboardButtonBase(CKeyboardButtonBase::Type type, QWidget *parent = Q_NULLPTR);
    ~CKeyboardButtonBase();

    CKeyboardButtonBase::Type type() const;

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    CKeyboardButtonBase::Type m_type;
    QIcon m_icon;
};

#endif // KEYBOARDBUTTONBASE_H
