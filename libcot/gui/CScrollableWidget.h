#ifndef CSCROLLABLEWIDGET_H
#define CSCROLLABLEWIDGET_H

#include <QScrollArea>
#include "../libcot/cot_global.h"

class COTWIDGETS_EXPORT CScrollableWidget : QScrollArea
{
    Q_OBJECT
public:
    explicit CScrollableWidget(QWidget *parent = Q_NULLPTR);
    ~CScrollableWidget();

};

#endif // CSCROLLABLEWIDGET_H
