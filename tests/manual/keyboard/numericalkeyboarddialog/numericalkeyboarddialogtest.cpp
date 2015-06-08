#include <QApplication>
#include <CPCWindow.h>
#include <QDebug>
#include "CNumericalKeyboardDialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (argc < 2 || QByteArray(argv[1]) == "double")
    {
        CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Double);
        dlg.setTitle("Enter a floating-point value");
        dlg.setDoubleValue(42);

        while (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
            double value = dlg.doubleValue();
            qDebug() << "value=" << value;
            dlg.setDoubleValue(value);
        }
    } else {
        CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Integer);
        dlg.setTitle("Enter an integer value");
        dlg.setIntegerValue(42);

        while (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
            int value = dlg.integerValue();
            qDebug() << "value=" << value;

            dlg.setIntegerValue(value);
        }
    }
    return 0;
}
