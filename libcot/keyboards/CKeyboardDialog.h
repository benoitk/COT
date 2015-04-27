#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "CKeyboardSpecialButton.h"

#include <QDialog>
class CKeyboardWidget;
class CVerticalButtonBar;
class CKeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CKeyboardDialog(QWidget *parent = Q_NULLPTR);
    ~CKeyboardDialog();

    QString stringValue() const;

private:
    CKeyboardWidget *m_keyboardWidget;
    CVerticalButtonBar *m_buttonBar;
};

#endif // KEYBOARDDIALOG_H
