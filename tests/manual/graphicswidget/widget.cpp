#include "widget.h"
#include "CGraphicsWidget.h"
#include <QVBoxLayout>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    CGraphicsWidget *graph = new CGraphicsWidget;
    vbox->addWidget(graph);
}

