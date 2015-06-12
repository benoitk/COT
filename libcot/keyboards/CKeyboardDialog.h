#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <CDialog.h>

class CKeyboardWidget;

class CKeyboardDialog : public CDialog
{
    Q_OBJECT

public:
    explicit CKeyboardDialog(QWidget *parent = Q_NULLPTR);
    ~CKeyboardDialog();

    QString stringValue() const;
    void setStringValue(const QString &value);

private:
    CKeyboardWidget *m_kwKeyboard;
};

#endif // KEYBOARDDIALOG_H
