#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class CNumericalKeyboardWidget;
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
private:
    CNumericalKeyboardWidget *m_keyboardWidget;
};

#endif // WIDGET_H
