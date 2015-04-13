#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "keyboardspecialbutton.h"

#include <QDialog>
class KeyboardWidget;
class KeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KeyboardDialog(QWidget *parent = Q_NULLPTR);
    ~KeyboardDialog();

    QString text() const;

private:
    KeyboardWidget *m_keyboardWidget;
};

#endif // KEYBOARDDIALOG_H
