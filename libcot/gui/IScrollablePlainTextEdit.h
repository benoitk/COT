#ifndef ISCROLLABLEPLAINTEXTEDIT_H
#define ISCROLLABLEPLAINTEXTEDIT_H

#include <QWidget>

class CScrollablePlainTextEdit;
class CVerticalButtonBar;

class IScrollablePlainTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit IScrollablePlainTextEdit(QWidget *parent = 0);
    virtual ~IScrollablePlainTextEdit();

    CScrollablePlainTextEdit *scrollableWidget() const;
    CVerticalButtonBar *buttonBar() const;

private:
    CScrollablePlainTextEdit *m_scrollableWidget;
    CVerticalButtonBar *m_verticalButtonBar;
};

#endif // ISCROLLABLEPLAINTEXTEDIT_H
