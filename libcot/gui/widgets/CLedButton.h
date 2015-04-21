#ifndef CLEDBUTTON_H
#define CLEDBUTTON_H

#include <QLabel>
#include <QIcon>

class CLedButton : public QLabel
{
    Q_OBJECT

public:
    explicit CLedButton(QWidget *parent = Q_NULLPTR);

    Qt::CheckState checkState() const;
    bool isChecked() const;

public slots:
    void setCheckState(Qt::CheckState state);
    void setChecked(bool checked);

private:
    Qt::CheckState m_checkState;
    QIcon m_icon;

    void updateIcon();
};

#endif // CLEDBUTTON_H
