#ifndef CSWITCHBUTTON_H
#define CSWITCHBUTTON_H

#include <QWidget>

class QButtonGroup;
class CToolButton;

class CSwitchButton : public QWidget
{
    Q_OBJECT

public:
    explicit CSwitchButton(QWidget *parent = Q_NULLPTR);

    bool isChecked() const;

public slots:
    void setChecked(bool checked);

private:
    QButtonGroup *m_buttonGroup;
    CToolButton *m_onButton;
    CToolButton *m_offButton;

private slots:
    void buttonClicked();

signals:
    void checkedChanged(bool checked);
};

#endif // CSWITCHBUTTON_H
