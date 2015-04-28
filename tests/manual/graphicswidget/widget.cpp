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
    graph->addCurve(lst, QStringLiteral("curve1"), CGraphicsWidget::createNewColor());
    lst.clear();
    for (int i = 0; i < 50; ++i) {
        lst << QPointF(i*30, i*15);
    }
    graph->addCurve(lst, QStringLiteral("curve2"), CGraphicsWidget::createNewColor());
}

