#ifndef NUMERICALKEYBOARDDIALOG_H
#define NUMERICALKEYBOARDDIALOG_H

#include <QDialog>
class NumericalKeyboardWidget;
class NumericalKeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NumericalKeyboardDialog(QWidget *parent=Q_NULLPTR);
    ~NumericalKeyboardDialog();

    double number() const;
private:
    NumericalKeyboardWidget *m_numericalKeyboardWidget;
};

#endif // NUMERICALKEYBOARDDIALOG_H
