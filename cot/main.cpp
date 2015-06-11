#include <QApplication>
#include <QStyleFactory>
#include <QFile>
#include <QDesktopWidget>
#include <QScreen>

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
    app.setApplicationDisplayName(QStringLiteral("COT"));
    app.setApplicationVersion(QStringLiteral("1.1.0"));
    app.setStyleSheet(applicationStyleSheet());
    app.setQuitOnLastWindowClosed(true);

    // Create automate and run it
    CControlerAutomate controlerAutomate;

    // The main PC Panel Window
    CPCWindow w;
#if defined(DEVICE_BUILD)
    w.showFullScreen();
    // NOTE: for some reason, the Qt version used here does not use the available size
    //       to workaround this problem, we manually set the fixed size to make the
    //       application use up all available screen space.
    w.setFixedSize(app.primaryScreen()->availableSize());
#else
    w.setFixedSize(QSize(800, 600));
    w.show();

#if defined(Q_OS_OSX)
    // Specific to Filipe secondary screen, can be removed at the end
    const QDesktopWidget *desktop = qApp->desktop();
    const QRect availableRect = desktop->availableGeometry(1);
    QRect windowGeometry = w.geometry();

    windowGeometry.moveCenter(availableRect.center());
    w.setGeometry(windowGeometry);
#endif
#endif

    return app.exec();
}
