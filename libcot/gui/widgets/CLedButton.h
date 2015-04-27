#ifndef CLEDBUTTON_H
#define CLEDBUTTON_H

#include <QLabel>
#include <QIcon>
#include <QVariant>

class CLedButton : public QLabel
{
    Q_OBJECT

public:
    explicit CLedButton(QWidget *parent = Q_NULLPTR);

    Qt::CheckState checkState() const;
    bool isChecked() const;

    QVariant userData() const;
    void setUserData(const QVariant &userData);

public slots:
    void setCheckState(Qt::CheckState state);
    void setChecked(bool checked);

private:
    Qt::CheckState m_checkState;
    QIcon m_icon;
    QVariant m_userData;

    void updateIcon();
};

#endif // CLEDBUTTON_H
