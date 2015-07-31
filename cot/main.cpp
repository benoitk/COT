#include <QApplication>
#include <QFile>
#include <QDesktopWidget>
#include <QScreen>

#include "CControlerAutomate.h"
#include "CPCWindow.h"
#include "CInitialTestWindow.h"
#include "StyleRepository.h"

int main(int argc, char *argv[])
{
#if defined(LIBCOT_STATIC_BUILD)
    // Needed for static linking of libcot
    Q_INIT_RESOURCE(cot_resources);
#endif

    // Create application
    QApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("COT"));
    app.setApplicationDisplayName(QStringLiteral("COT"));
    app.setApplicationVersion(QStringLiteral("1.1.0"));
    app.setQuitOnLastWindowClosed(true);

#ifdef DEVICE_BUILD
    app.setOverrideCursor(QCursor(Qt::BlankCursor));
#endif

    // Set default uniform style
    StyleRepository::installStyle();

    // Set default font
    StyleRepository::installFont();

    // Create automate and run it
    CControlerAutomate controlerAutomate;

    // The main PC Panel Window
    CPCWindow w;
    CInitialTestsWindow initialTestWindow(&w);

#if defined(DEVICE_BUILD)
    initialTestWindow.showFullScreen();
    w.showFullScreen();
    // NOTE: for some reason, the Qt version used here does not use the available size
    //       to workaround this problem, we manually set the fixed size to make the
    //       application use up all available screen space.
    w.setFixedSize(app.primaryScreen()->availableSize());
#else
    if (StyleRepository::screenSize() == StyleRepository::SevenInch){
        w.setFixedSize(QSize(800, 480));
        initialTestWindow.setFixedSize(QSize(800, 480));

    }
    else{
        w.setFixedSize(QSize(1024, 600));
        initialTestWindow.setFixedSize(QSize(1024, 600));
    }
    initialTestWindow.exec();
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
