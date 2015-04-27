#ifndef NUMERICALKEYBOARDDIALOG_H
#define NUMERICALKEYBOARDDIALOG_H

#include <QDialog>
#include "CNumericalKeyboardWidget.h"
class CNumericalKeyboardWidget;
class CVerticalButtonBar;
class CNumericalKeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CNumericalKeyboardDialog(QWidget *parent=Q_NULLPTR);
    explicit CNumericalKeyboardDialog(CNumericalKeyboardWidget::Mode mode, QWidget *parent=Q_NULLPTR);
    ~CNumericalKeyboardDialog();

    int integerValue() const;
    double doubleValue() const;
private:
    CNumericalKeyboardWidget *m_numericalKeyboardWidget;
    CVerticalButtonBar *m_buttonBar;

    void initialize(CNumericalKeyboardWidget::Mode mode);
};

#endif // NUMERICALKEYBOARDDIALOG_H
