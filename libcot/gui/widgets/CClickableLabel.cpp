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

QVariant CClickableLabel::userData() const
{
    return m_userData;
}

void CClickableLabel::setUserData(const QVariant &userData)
{
    m_userData = userData;
}

