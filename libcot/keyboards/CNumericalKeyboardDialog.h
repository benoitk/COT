#ifndef NUMERICALKEYBOARDDIALOG_H
#define NUMERICALKEYBOARDDIALOG_H

#include <CDialog.h>

#include "CNumericalKeyboardWidget.h"

class LIBCOT_EXPORT CNumericalKeyboardDialog : public CDialog
{
    Q_OBJECT
public:
    explicit CNumericalKeyboardDialog(QWidget *parent=Q_NULLPTR);
    explicit CNumericalKeyboardDialog(CNumericalKeyboardWidget::Mode mode, QWidget *parent=Q_NULLPTR);
    ~CNumericalKeyboardDialog();

    int integerValue() const;
    void setIntegerValue(int value);

    float floatValue() const;
    void setFloatValue(float value, int precision);

    static bool getInteger(int &value, const QString &title, QWidget *parent = Q_NULLPTR);

private:
    CNumericalKeyboardWidget *m_nkwKeyboard;

    void initialize(CNumericalKeyboardWidget::Mode mode);
};

#endif // NUMERICALKEYBOARDDIALOG_H
