#include <QApplication>
#include "../../../../cot/keyboards/keyboardwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyboardWidget *w = new KeyboardWidget();
    w->show();
    return a.exec();
}
