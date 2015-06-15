#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include <QPushButton>
#include <QVariant>

// This class represent rounded rect gray push button
class CPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CPushButton(QWidget *parent = Q_NULLPTR);
    ~CPushButton();

    QVariant userData() const;
    void setUserData(const QVariant &userData);

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QVariant m_userData;
};

#endif // CPUSHBUTTON_H
