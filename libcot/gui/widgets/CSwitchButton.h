#ifndef CSWITCHBUTTON_H
#define CSWITCHBUTTON_H

#include <QWidget>
#include <QVariant>

class QButtonGroup;
class CToolButton;

class CSwitchButton : public QWidget
{
    Q_OBJECT

public:
    explicit CSwitchButton(QWidget *parent = Q_NULLPTR);

    bool isChecked() const;

    QVariant userData() const;
    void setUserData(const QVariant &userData);

public slots:
    void setChecked(bool checked);

private:
    QButtonGroup *m_buttonGroup;
    CToolButton *m_onButton;
    CToolButton *m_offButton;
    QVariant m_userData;

private slots:
    void buttonClicked();

signals:
    void clicked();
    void checkedChanged(bool checked);
};

#endif // CSWITCHBUTTON_H
