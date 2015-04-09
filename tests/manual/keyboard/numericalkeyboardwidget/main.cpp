#include <QApplication>
#include "../../../../cot/keyboards/numericalkeyboardwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NumericalKeyboardWidget *w = new NumericalKeyboardWidget();
    w->show();
    return a.exec();
}
