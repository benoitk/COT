#include <QApplication>
#include <CPCWindow.h>
#include <QDebug>
#include "CNumericalKeyboardDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Double);
    dlg.setTitle("Enter a new value");
    dlg.setDoubleValue(42);

    while (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        double value = dlg.doubleValue();
        qDebug() << "value=" << value;

        dlg.setDoubleValue(value);
    }
    return 0;
}
