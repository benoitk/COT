#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>

namespace Ui {
class CKeyboardDialog;
}

class CKeyboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CKeyboardDialog(QWidget *parent = Q_NULLPTR);
    ~CKeyboardDialog();

    void setTitle(const QString &title);

    QString stringValue() const;
    void setStringValue(const QString &value);

private:
    Ui::CKeyboardDialog *ui;
};

#endif // KEYBOARDDIALOG_H
