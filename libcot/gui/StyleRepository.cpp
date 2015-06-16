#include "StyleRepository.h"
#include <CProxyStyle.h>
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <QScreen>
#include <qfont.h>

StyleRepository::ScreenSize StyleRepository::screenSize()
{
#if defined(DEVICE_BUILD)
    const QSize sz = qApp->primaryScreen()->availableSize();
    if (sz == QSize(800, 480))
        return SevenInch;
    if (sz == QSize(1024, 600))
        return TenInch;
    // Default value for unknown screens
    return SevenInch;
#else
    // Default value for the desktop
    return SevenInch;
#endif
}

QSize StyleRepository::configuratorButtonSize()
{
    switch (screenSize()) {
    case SevenInch:
        return QSize(30, 30);
    case TenInch:
        return QSize(50, 50);
    }
    return QSize(); // not reached
}

QSize StyleRepository::measuresStreamButtonSize()
{
    switch (screenSize()) {
    case SevenInch:
        return QSize(50, 50);
    case TenInch:
        return QSize(50, 50);
    }
    return QSize(); // not reached
}

QSize StyleRepository::playStopButtonSize()
{
    switch (screenSize()) {
    case SevenInch:
        return QSize(30, 30);
    case TenInch:
        return QSize(30, 30);
    }
    return QSize(); // not reached
}

QSize StyleRepository::verticalBarButtonSize()
{
    switch (screenSize()) {
    case SevenInch:
        return QSize(50, 50);
    case TenInch:
        return QSize(75, 75);
    }
    return QSize(); // not reached
}

QSize StyleRepository::keyboardButtonSize()
{
    switch (screenSize()) {
    case SevenInch:
        return QSize(50, 50);
    case TenInch:
        return QSize(50, 50);
    }
    return QSize(); // not reached
}

void StyleRepository::installFont()
{
    static bool done = false;
    if (!done) { // do this only once!
        done = true;
        QFont defaultFont = QApplication::font(); // let the OS decide on the font name. Or should we specify it here?
        defaultFont.setPointSize(12);
        QApplication::setFont(defaultFont);
    }
}

void StyleRepository::installStyle()
{
    // White background for windows
    QPalette pal = QApplication::palette();
    pal.setColor(QPalette::Window, QColor(Qt::white));
    QApplication::setPalette(pal);

    // Uniform style and proxy
    QStyle *baseStyle = QStyleFactory::create("Fusion");
    QProxyStyle *proxy = new CProxyStyle(baseStyle);
    QApplication::setStyle(proxy);
}

QSize StyleRepository::extraButtonSize()
{
    return QSize(0, 8);
}

QFont StyleRepository::tabBarFont()
{
    QFont font = QApplication::font();
    font.setPointSize(12);
    return font;
}

QFont StyleRepository::measureFont()
{
    QFont font = QApplication::font();
    font.setPointSize(24);
    return font;
}

StyleRepository::StyleRepository()
{
}
