#include <QApplication>
#include <CPCWindow.h>
#include <QDebug>
#include "CNumericalKeyboardDialog.h"
#include "StyleRepository.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    StyleRepository::installStyle();
    StyleRepository::installFont();

    if (argc < 2 || QByteArray(argv[1]) == "double")
    {
        CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Double);
        dlg.setTitle("Enter a floating-point value");
        dlg.setFloatValue(42);

        while (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
            float value = dlg.floatValue();
            qDebug() << "value=" << value;
            dlg.setFloatValue(value);
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
