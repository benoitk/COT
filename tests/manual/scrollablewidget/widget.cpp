#include "widget.h"
#include "CScrollableWidget.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QLabel>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);

    QToolBar *bar = new QToolBar(this);
    vbox->addWidget(bar);

    QWidget *myWidget = new QWidget;
    QVBoxLayout *myWidgetLayout = new QVBoxLayout;
    myWidget->setLayout(myWidgetLayout);
    for (int i = 0; i < 100 ; ++i) {
        QLabel *label = new QLabel(QStringLiteral("label %1").arg(i));
        myWidgetLayout->addWidget(label);
    }

    CScrollableWidget *scrollablewidget = new CScrollableWidget(this);
    scrollablewidget->setWidget(myWidget);
    vbox->addWidget(scrollablewidget);
    bar->addAction(scrollablewidget->moveUp());
    bar->addAction(scrollablewidget->moveDown());

}

