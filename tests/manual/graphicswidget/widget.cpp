#include "widget.h"
#include "CGraphicsWidget.h"
#include <QVBoxLayout>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    CGraphicsWidget *graph = new CGraphicsWidget;
    vbox->addWidget(graph);
    QList<QPointF> lst;
    for (int i = 0; i < 50; ++i) {
        lst << QPointF(i*10, i+10);
    }
    graph->addCurves(lst, Qt::red);
    lst.clear();
    for (int i = 0; i < 50; ++i) {
        lst << QPointF(i*30, i*15);
    }
    graph->addCurves(lst, Qt::green);
}

