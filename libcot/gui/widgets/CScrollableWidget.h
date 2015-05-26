#ifndef CSCROLLABLEWIDGET_H
#define CSCROLLABLEWIDGET_H

#include <QScrollArea>
#include <QPlainTextEdit>
#include "cot_global.h"
class QAction;
class LIBCOT_EXPORT CScrollableWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit CScrollableWidget(QWidget *parent = Q_NULLPTR);
    explicit CScrollableWidget(bool scrollable, QWidget *parent = Q_NULLPTR);
    ~CScrollableWidget();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    bool scrollable() const;
    void setScrollable(bool scrollable);

    QAction *moveDown() const;
    QAction *moveUp() const;

    void setScrollableWidget(QWidget *w);

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;

private slots:
    void slotMoveUp();
    void slotMoveDown();

private:
    bool m_scrollable;
    QAction *m_moveUp;
    QAction *m_moveDown;

    void updateActions();
};

// CScrollablePlainTextEdit

class LIBCOT_EXPORT CScrollablePlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CScrollablePlainTextEdit(QWidget *parent = Q_NULLPTR);
    ~CScrollablePlainTextEdit();

    QAction *moveDown() const;

    QAction *moveUp() const;

protected:
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void slotMoveUp();
    void slotMoveDown();

private:
    void updateActions();
    QAction *m_moveUp;
    QAction *m_moveDown;
};

#endif // CSCROLLABLEWIDGET_H
