#include "CPushButton.h"

#include <QPainter>

namespace {
    const int CORNER_RADIUS = 5;
}

CPushButton::CPushButton(QWidget *parent)
    : QPushButton(parent)
{
    QPalette pal = palette();
    pal.setColor(backgroundRole(), QColor(Qt::gray));
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
    painter.setBrush(palette().color(backgroundRole()).lighter(isDown() ? 120 : 0));
    painter.drawRoundedRect(rect(), CORNER_RADIUS, CORNER_RADIUS);

    painter.setPen(palette().color(foregroundRole()));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(rect(), Qt::AlignCenter, text());
}
