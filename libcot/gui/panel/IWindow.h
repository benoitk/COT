#ifndef IWINDOW_H
#define IWINDOW_H

#include <QWidget>
#include "cot_global.h"

/**
 * @brief The IWindow class is a pure virtual base class
 * that is used to create a window with a return button and a central scroll area.
 */

class CScrollableWidget;
class CVerticalButtonBar;

class LIBCOT_EXPORT IWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IWindow(QWidget *parent = Q_NULLPTR);

protected:
    /// underlying main widget
    void setMainWidget(QWidget *widget);
    QWidget *mainWidget();

    /// accessors for the vertical button bar and scrollable area
    CVerticalButtonBar *buttonBar();
    CScrollableWidget *scrollable();

    /**
     * @brief Initialize the window here
     */
    virtual void setupWindow() = 0;

private:
    CScrollableWidget *m_scrollableWidget;
    CVerticalButtonBar *m_buttonBar;
};

#endif // IWINDOW_H
