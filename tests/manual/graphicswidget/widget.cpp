#include "widget.h"
#include "CGraphicsWidget.h"
#include <QVBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    CGraphicsWidget *graph = new CGraphicsWidget;
    vbox->addWidget(graph);
    for (int i = 0; i < 50; ++i) {
        graph->addOrUpdateCurve(i * 10, QStringLiteral("curve1"));
        graph->addOrUpdateCurve(i * 15, QStringLiteral("curve2"));
        graph->doneUpdatingPlotting();
    }
}

