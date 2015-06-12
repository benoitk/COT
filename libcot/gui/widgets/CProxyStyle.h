#ifndef PROXYSTYLE_H
#define PROXYSTYLE_H

#include <QProxyStyle>

#include "cot_global.h"

class LIBCOT_EXPORT CProxyStyle : public QProxyStyle
{
public:
    CProxyStyle(QStyle *style) : QProxyStyle(style) {}

    int styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const Q_DECL_OVERRIDE;
    int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const Q_DECL_OVERRIDE;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const Q_DECL_OVERRIDE;

    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const Q_DECL_OVERRIDE;
};

#endif
