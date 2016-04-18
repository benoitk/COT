#include "CPushButton.h"

#include <QPainter>
#include <StyleRepository.h>

namespace {
    const int CORNER_RADIUS = 5;
}

CPushButton::CPushButton(QWidget *parent)
    : QPushButton(parent)
{
    QPalette pal = palette();
    pal.setColor(backgroundRole(), QColor(Qt::darkGray));
    pal.setColor(foregroundRole(), QColor(Qt::white));
    setPalette(pal);
}

CPushButton::~CPushButton()
{
}

void CPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    if(isDown() || !isEnabled())
        painter.setBrush(Qt::gray);
    else
        painter.setBrush(Qt::darkGray);
    painter.drawRoundedRect(rect(), CORNER_RADIUS, CORNER_RADIUS);

    painter.setPen(palette().color(foregroundRole()));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(rect(), Qt::AlignCenter | Qt::TextHideMnemonic, text());
}

QVariant CPushButton::userData() const
{
    return m_userData;
}

void CPushButton::setUserData(const QVariant &userData)
{
    m_userData = userData;
}

QSize CPushButton::sizeHint() const
{
    return QPushButton::sizeHint() + StyleRepository::extraButtonSize();
}

