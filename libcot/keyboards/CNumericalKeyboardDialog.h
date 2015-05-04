#ifndef NUMERICALKEYBOARDDIALOG_H
#define NUMERICALKEYBOARDDIALOG_H

#include <QDialog>

#include "CNumericalKeyboardWidget.h"

namespace Ui {
class CNumericalKeyboardDialog;
}

class CNumericalKeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CNumericalKeyboardDialog(QWidget *parent=Q_NULLPTR);
    explicit CNumericalKeyboardDialog(CNumericalKeyboardWidget::Mode mode, QWidget *parent=Q_NULLPTR);
    ~CNumericalKeyboardDialog();

    void setTitle(const QString &title);

    int integerValue() const;
    void setIntegerValue(int value);

    double doubleValue() const;
    void setDoubleValue(double value);

private:
    Ui::CNumericalKeyboardDialog *ui;

    void initialize(CNumericalKeyboardWidget::Mode mode);
};

#endif // NUMERICALKEYBOARDDIALOG_H
