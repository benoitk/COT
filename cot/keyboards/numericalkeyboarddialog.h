#ifndef NUMERICALKEYBOARDDIALOG_H
#define NUMERICALKEYBOARDDIALOG_H

#include <QDialog>

class NumericalKeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NumericalKeyboardDialog(QWidget *parent=Q_NULLPTR);
    ~NumericalKeyboardDialog();
};

#endif // NUMERICALKEYBOARDDIALOG_H
