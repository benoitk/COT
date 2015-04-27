#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = Q_NULLPTR);
};

#endif // WIDGET_H
