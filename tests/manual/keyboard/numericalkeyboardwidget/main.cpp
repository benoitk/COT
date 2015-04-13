#include <QApplication>
#include "CNumericalKeyboardWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CNumericalKeyboardWidget *w = new CNumericalKeyboardWidget();
    w->show();
    return a.exec();
}
