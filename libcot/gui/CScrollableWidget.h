#ifndef CSCROLLABLEWIDGET_H
#define CSCROLLABLEWIDGET_H

#include <QScrollArea>
#include "cot_global.h"
class QAction;
class COTWIDGETS_EXPORT CScrollableWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit CScrollableWidget(QWidget *parent = Q_NULLPTR);
    ~CScrollableWidget();

    QAction *moveDown() const;

    QAction *moveUp() const;

private Q_SLOTS:
    void slotMoveUp();
    void slotMoveDown();

private:
    QAction *m_moveUp;
    QAction *m_moveDown;
};

#endif // CSCROLLABLEWIDGET_H
