#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include "keyboardspecialbutton.h"

#include <QWidget>
class QGridLayout;
class QVBoxLayout;
class QLineEdit;
class KeyboardNormalButton;

class KeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardWidget(QWidget *parent = Q_NULLPTR);
    ~KeyboardWidget();

Q_SIGNALS:
    void returnPressed();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotShiftToggled();

    void slotCapsLockToggled();

    void slotButtonClicked(const QChar &character);
    void slotSpecialButtonClicked(Qt::Key key);
private:
    void keyClicked();
    void initializeKeyboardLayout();
    QString m_currentLanguage;
    QLineEdit *m_lineEdit;
    QGridLayout *m_keyboardLayout;
    QVBoxLayout *m_mainLayout;
    QList<KeyboardSpecialButton *> m_shiftButtons;
    QList<KeyboardNormalButton *> m_normalButtons;
    bool m_capsLockOn;
    bool m_shiftOn;
};

#endif // KEYBOARDWIDGET_H
