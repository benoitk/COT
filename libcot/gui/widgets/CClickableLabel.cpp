#include "CClickableLabel.h"

CClickableLabel::CClickableLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
}

CClickableLabel::CClickableLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{
}

void CClickableLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QLabel::mouseReleaseEvent(ev);
    emit clicked();
}
