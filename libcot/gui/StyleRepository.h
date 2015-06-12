#ifndef STYLEREPOSITORY_H
#define STYLEREPOSITORY_H

#include <QSize>

class StyleRepository
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

private:
    StyleRepository();
};

#endif // STYLEREPOSITORY_H
