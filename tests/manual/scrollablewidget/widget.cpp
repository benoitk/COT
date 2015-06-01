#include "widget.h"
#include "CScrollableWidget.h"
#include "CScrollablePagerWidget.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QTextEdit>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);

    QToolBar *bar = new QToolBar(this);
    vbox->addWidget(bar);

    CScrollablePagerWidget *myWidget = new CScrollablePagerWidget;
    QVBoxLayout *myWidgetLayout = new QVBoxLayout;
    myWidget->setLayout(myWidgetLayout);
    for (int i = 0; i < 100 ;) {
        QLabel *label = new QLabel(QStringLiteral("label %1").arg(i));
        myWidgetLayout->addWidget(label);
        ++i;
        QTextEdit *textEdit = new QTextEdit;
        textEdit->setText(QStringLiteral("textedit %1").arg(i));
        myWidgetLayout->addWidget(textEdit);
        ++i;
    }

    CScrollableWidget *scrollablewidget = new CScrollableWidget(this);
    scrollablewidget->setScrollablePagerWidget(myWidget);
    vbox->addWidget(scrollablewidget);
    bar->addAction(scrollablewidget->moveUp());
    bar->addAction(scrollablewidget->moveDown());

}

