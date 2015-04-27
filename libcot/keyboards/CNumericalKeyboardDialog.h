#ifndef NUMERICALKEYBOARDDIALOG_H
#define NUMERICALKEYBOARDDIALOG_H

#include <QDialog>
class CNumericalKeyboardWidget;
class CNumericalKeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CNumericalKeyboardDialog(QWidget *parent=Q_NULLPTR);
    ~CNumericalKeyboardDialog();

    double number() const;
private:
    CNumericalKeyboardWidget *m_numericalKeyboardWidget;
};

#endif // NUMERICALKEYBOARDDIALOG_H
