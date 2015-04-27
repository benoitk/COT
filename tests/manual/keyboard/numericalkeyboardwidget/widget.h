#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class CNumericalKeyboardWidget;
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = Q_NULLPTR);
private:
    CNumericalKeyboardWidget *m_keyboardWidget;
};

#endif // WIDGET_H
