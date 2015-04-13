#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include "CKeyboardNormalButton.h"
#include "../../libcot/cot_global.h"

#include <QWidget>
class QGridLayout;
class QVBoxLayout;
class QLineEdit;
class CKeyboardNormalButton;
class CKeyboardSpecialButton;
class COTWIDGETS_EXPORT CKeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CKeyboardWidget(QWidget *parent = Q_NULLPTR);
    ~CKeyboardWidget();

    QString text() const;
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
    QList<CKeyboardSpecialButton *> m_shiftButtons;
    QList<CKeyboardNormalButton *> m_normalButtons;
    bool m_capsLockOn;
    bool m_shiftOn;
};

#endif // KEYBOARDWIDGET_H
