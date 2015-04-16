#include "widget.h"
#include "CScrollableWidget.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);

    QToolBar *bar = new QToolBar(this);
    vbox->addWidget(bar);

    CScrollableWidget *scrollablewidget = new CScrollableWidget(this);
    vbox->addWidget(scrollablewidget);
    bar->addAction(scrollablewidget->moveUp());
    bar->addAction(scrollablewidget->moveDown());
}

