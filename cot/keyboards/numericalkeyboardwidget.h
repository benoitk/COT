#ifndef NUMERICALKEYBOARDWIDGET_H
#define NUMERICALKEYBOARDWIDGET_H

#include <QWidget>
class QLineEdit;
class QVBoxLayout;
class KeyboardNormalButton;
class NumericalKeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NumericalKeyboardWidget(QWidget *parent = Q_NULLPTR);
    ~NumericalKeyboardWidget();

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
private:
    void updateDigitalText();
    KeyboardNormalButton *createButton(QChar character);
    void initializeKeyboardLayout();
    QVBoxLayout *m_mainLayout;
    QLineEdit *m_lineEdit;
    KeyboardNormalButton *m_digitalButton;
};

#endif // NUMERICALKEYBOARDWIDGET_H
