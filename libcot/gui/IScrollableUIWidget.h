#ifndef ISCROLLABLEUIWIDGET_H
#define ISCROLLABLEUIWIDGET_H

#include <QWidget>

class CScrollableWidget;
class CVerticalButtonBar;

class IScrollableUIWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IScrollableUIWidget(QWidget *parent = 0);
    virtual ~IScrollableUIWidget();

    CScrollableWidget *scrollableWidget() const;
    CVerticalButtonBar *buttonBar() const;

private:
    CScrollableWidget *m_scrollableWidget;
    CVerticalButtonBar *m_verticalButtonBar;
};

#endif // ISCROLLABLEUIWIDGET_H
