#ifndef STYLEREPOSITORY_H
#define STYLEREPOSITORY_H

#include <QFont>
#include <QSize>
#include "cot_global.h"

class LIBCOT_EXPORT StyleRepository
{
public:

    enum ScreenSize
    {
        SevenInch,
        TenInch
    };
    static ScreenSize screenSize();

    // size of the new/delete/... buttons in the configurator
    static QSize configuratorButtonSize();

    // size of the stream button near measures in the main screen
    static QSize measuresStreamButtonSize();

    // size of the play/stop buttons (e.g. in the maintenance tab)
    static QSize playStopButtonSize();

    // size of the buttons in the vertical bar on the right
    static QSize verticalBarButtonSize();

    // size of the buttons in the keyboard dialogs
    static QSize keyboardButtonSize();

    // Set default font
    static void installFont();

    // Set default widget style
    static void installStyle();

    // Additional size for rounded push buttons
    static QSize extraButtonSize();

    // Font for tab bars
    static QFont tabBarFont();

    // Font for measures in the main screen
    static QFont measureFont();

private:
    StyleRepository();
};

#endif // STYLEREPOSITORY_H
