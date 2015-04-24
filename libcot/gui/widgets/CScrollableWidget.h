#ifndef CSCROLLABLEWIDGET_H
#define CSCROLLABLEWIDGET_H

#include <QScrollArea>
#include "cot_global.h"
class QAction;
class LIBCOT_EXPORT CScrollableWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit CScrollableWidget(QWidget *parent = Q_NULLPTR);
    ~CScrollableWidget();

    QAction *moveDown() const;

    QAction *moveUp() const;

    void setScrollableWidget(QWidget *w);

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
