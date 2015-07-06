#include "StyleRepository.h"
#include <CProxyStyle.h>
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <QScreen>
#include <QFontInfo>
#include <QFont>
#include <QFontDatabase>

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
        return QSize(44, 44);
    case TenInch:
        return QSize(65, 65);
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

        static const char* s_fonts[] = {
            //"fonts/LiberationSansNarrow-BoldItalic.ttf",
            //"fonts/LiberationSansNarrow-Bold.ttf",
            //"fonts/LiberationSansNarrow-Italic.ttf",
            //"fonts/LiberationSansNarrow-Regular.ttf",

            "fonts/LiberationSans-BoldItalic.ttf",
            "fonts/LiberationSans-Bold.ttf",
            "fonts/LiberationSans-Italic.ttf",
            "fonts/LiberationSans-Regular.ttf"
            // The last font is the main font
        };

        QStringList mainFontFamilies;
        for (size_t i = 0 ; i < sizeof(s_fonts) / sizeof(*s_fonts) ; ++i ) {
            int result = QFontDatabase::addApplicationFont(QString(":/") + s_fonts[i]);
            if (result == -1) {
                qWarning() << "Couldn't load builtin font" << s_fonts[i];
            } else {
                //qDebug() << QFontDatabase::applicationFontFamilies(result);
                mainFontFamilies = QFontDatabase::applicationFontFamilies(result);
            }
        }

        //qDebug() << "system font" << qApp->font().family() << "resolved to" << QFontInfo(qApp->font()).family();
        QFont defaultFont(mainFontFamilies.at(0), 12);
        QApplication::setFont(defaultFont);
        //qDebug() << "our font" << qApp->font().family() << "resolved to" << QFontInfo(qApp->font()).family();
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
    // When changing this, ensure that the tabs of the configurator still fit ;)
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
