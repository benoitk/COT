#ifndef CCLICKABLELABEL_H
#define CCLICKABLELABEL_H

#include <QLabel>
#include <QVariant>

class CClickableLabel : public QLabel
{
    Q_OBJECT

public:
    CClickableLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    CClickableLabel(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0);

    QVariant userData() const;
    void setUserData(const QVariant &userData);

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;

private:
    QVariant m_userData;
};

#endif // CCLICKABLELABEL_H
