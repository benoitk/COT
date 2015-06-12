#include "StyleRepository.h"
#include <CProxyStyle.h>
#include <QApplication>
#include <QStyleFactory>
#include <qfont.h>

QSize StyleRepository::configuratorButtonSize()
{
    return QSize(30, 30);
}

QSize StyleRepository::playStopButtonSize()
{
    return QSize(30, 30);
}

QSize StyleRepository::verticalBarButtonSize()
{
    return QSize(50, 50);
}

QSize StyleRepository::keyboardButtonSize()
{
    return QSize(50, 50);
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

StyleRepository::StyleRepository()
{
}
