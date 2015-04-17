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
    // Needed for static linking of libcot
    Q_INIT_RESOURCE(cot_resources);

    // Set default uniform style
    QApplication::setStyle(QStyleFactory::create("Fusion"));

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
#if defined(DESKTOP_BUILD)
    w.setFixedSize(QSize(800, 600));
    w.show();
#else
    w.showFullScreen();
#endif

    return app.exec();
}
