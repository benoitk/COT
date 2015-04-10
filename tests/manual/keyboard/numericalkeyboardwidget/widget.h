#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class NumericalKeyboardWidget;
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
private:
    NumericalKeyboardWidget *m_keyboardWidget;
};

#endif // WIDGET_H
