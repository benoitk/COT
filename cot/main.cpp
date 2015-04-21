#include <QApplication>
#include <QStyleFactory>
#include <QFile>

#include "CControlerAutomate.h"
#include "CPCWindow.h"

QString applicationStyleSheet()
{
    QFile file("://qss/cot.qss");

    if (file.open(QIODevice::ReadOnly)) {
        return QString::fromUtf8(file.readAll());
    }

    return QString();
}

int main(int argc, char *argv[])
{
#if defined(LIBCOT_STATIC_BUILD)
    // Needed for static linking of libcot
    Q_INIT_RESOURCE(cot_resources);
#endif

    // Set default uniform style
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // White background for windows
    QPalette pal = QApplication::palette();
    pal.setColor(QPalette::Window, QColor(Qt::white));
    QApplication::setPalette(pal);

    // Create application
    QApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("COT"));
    app.setApplicationVersion(QStringLiteral("1.1.0"));
    app.setStyleSheet(applicationStyleSheet());
    app.setQuitOnLastWindowClosed(true);

    // Create automate and run it
    CControlerAutomate controlerAutomate;

    // The main PC Panel Window
    CPCWindow w;
#if defined(DEVICE_BUILD)
    w.showFullScreen();
#else
    w.setFixedSize(QSize(800, 600));
    w.show();
#endif

    return app.exec();
}
