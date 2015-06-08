#ifndef NUMERICALKEYBOARDWIDGET_H
#define NUMERICALKEYBOARDWIDGET_H

#include <QWidget>
#include "cot_global.h"
class QLineEdit;
class QVBoxLayout;
class CKeyboardNormalButton;
class LIBCOT_EXPORT CNumericalKeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    enum Mode {
        Integer = 0,
        Double
    };

    explicit CNumericalKeyboardWidget(QWidget *parent = Q_NULLPTR);
    explicit CNumericalKeyboardWidget(CNumericalKeyboardWidget::Mode mode, QWidget *parent = Q_NULLPTR);
    ~CNumericalKeyboardWidget();

    CNumericalKeyboardWidget::Mode mode() const;
    void setMode(const CNumericalKeyboardWidget::Mode &mode);

    int integerNumber() const;
    void setIntegerNumber(int number);

    double doubleNumber() const;
    void setDoubleNumber(double number);

Q_SIGNALS:
    void returnPressed();

protected:
    bool event(QEvent *ev) Q_DECL_OVERRIDE;
private slots:
    void slotChangeSign(bool);
    void slotButtonClicked(QChar character);
    void slotDigitalButtonPressed(QChar character);
    void slotBlackspaceButtonClicked(Qt::Key);
private:
    QLocale lineEditLocale() const;
    void updateDigitalText();
    void setFixedText(const QString &text);
    QString formatDouble(double value, int maxDecimals) const;
    CKeyboardNormalButton *createButton(QChar character);
    void initializeKeyboardLayout();
    QVBoxLayout *m_mainLayout;
    QLineEdit *m_lineEdit;
    CKeyboardNormalButton *m_digitalButton;
    CNumericalKeyboardWidget::Mode m_mode;
};

#endif // NUMERICALKEYBOARDWIDGET_H
