#ifndef STYLEREPOSITORY_H
#define STYLEREPOSITORY_H

#include <QSize>
#include "cot_global.h"

class LIBCOT_EXPORT StyleRepository
{
public:
    // size of the new/delete/... buttons in the configurator
    static QSize configuratorButtonSize();

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

private:
    StyleRepository();
};

#endif // STYLEREPOSITORY_H
