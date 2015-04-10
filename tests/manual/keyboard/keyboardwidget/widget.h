#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLocale>
class KeyboardWidget;
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = Q_NULLPTR);
private slots:
    void slotChangeLocale(QLocale::Language local);
private:
    KeyboardWidget *m_keyboardWidget;
};

#endif // WIDGET_H
