#include "widget.h"
#include "CGraphicsWidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include <CPlotObject.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    CGraphicsWidget *graph = new CGraphicsWidget;
    vbox->addWidget(graph);

    CPlotObject *curve1 = new CPlotObject(Qt::red);
    CPlotObject *curve2 = new CPlotObject(Qt::blue);
    graph->addPlotObject(curve1);
    graph->addPlotObject(curve2);
    for (int i = 0; i < 50; ++i) {
        graph->addPoint(i * 10, curve1);
        graph->addPoint(i * 15, curve2);
        graph->doneUpdatingPlotting();
    }
}

