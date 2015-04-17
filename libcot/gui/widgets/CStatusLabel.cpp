#include "CStatusLabel.h"

CStatusLabel::CStatusLabel(QWidget *parent)
    : QLabel(parent)
{
    QPalette pal = palette();
    pal.setColor(backgroundRole(), QColor(Qt::black));
    pal.setColor(foregroundRole(), QColor(Qt::white));
    setPalette(pal);
}

CStatusLabel::~CStatusLabel()
{
}
