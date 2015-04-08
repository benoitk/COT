#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "keyboardspecialbutton.h"

#include <QDialog>
class QGridLayout;
class QVBoxLayout;
class QLineEdit;
class KeyboardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KeyboardDialog(QWidget *parent = Q_NULLPTR);
    ~KeyboardDialog();

private Q_SLOTS:
    void slotShiftToggled();

    void slotCapsLockToggled();
private:
    void initializeKeyboardLayout();

    QLineEdit *mLineEdit;
    QGridLayout *mKeyboardLayout;
    QVBoxLayout *mMainLayout;
    QList<KeyboardSpecialButton *> mShiftButtons;
    bool mCapsLockOn;
    bool mShiftOn;
};

#endif // KEYBOARDDIALOG_H
