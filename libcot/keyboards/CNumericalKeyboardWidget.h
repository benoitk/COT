#ifndef NUMERICALKEYBOARDWIDGET_H
#define NUMERICALKEYBOARDWIDGET_H

#include <QWidget>
#include "../../libcot/cot_global.h"
class QLineEdit;
class QVBoxLayout;
class CKeyboardNormalButton;
class LIBCOT_EXPORT CNumericalKeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CNumericalKeyboardWidget(QWidget *parent = Q_NULLPTR);
    ~CNumericalKeyboardWidget();

    double number() const;
Q_SIGNALS:
    void returnPressed();

protected:
    bool event(QEvent *ev) Q_DECL_OVERRIDE;
private slots:
    void slotChangeSign(bool);
    void slotButtonClicked(QChar character);
    void slotSpecialButtonClicked(Qt::Key key);
    void slotDigitalButtonPressed(QChar character);
    void slotBlackspaceButtonClicked(Qt::Key);
private:
    void updateDigitalText();
    CKeyboardNormalButton *createButton(QChar character);
    void initializeKeyboardLayout();
    QVBoxLayout *m_mainLayout;
    QLineEdit *m_lineEdit;
    CKeyboardNormalButton *m_digitalButton;
};

#endif // NUMERICALKEYBOARDWIDGET_H
