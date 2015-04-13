#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "CKeyboardSpecialButton.h"

#include <QDialog>
class CKeyboardWidget;
class CKeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CKeyboardDialog(QWidget *parent = Q_NULLPTR);
    ~CKeyboardDialog();

    QString text() const;

private:
    CKeyboardWidget *m_keyboardWidget;
};

#endif // KEYBOARDDIALOG_H
