#ifndef CCLICKABLELABEL_H
#define CCLICKABLELABEL_H

#include <QLabel>

class CClickableLabel : public QLabel
{
    Q_OBJECT

public:
    CClickableLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    CClickableLabel(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0);

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
};

#endif // CCLICKABLELABEL_H
