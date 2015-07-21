#ifndef CSCROLLABLEWIDGET_H
#define CSCROLLABLEWIDGET_H

#include <QScrollArea>
#include <QPlainTextEdit>

#include "cot_global.h"

class QAction;
class CScrollablePagerWidget;

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

    void setScrollablePagerWidget(CScrollablePagerWidget *w);
    CScrollablePagerWidget *scrollablePagerWidget() const;

    void updatePageHeight();
    void updateActions();

    int getPageStep() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;

private slots:
    void slotMoveUp();
    void slotMoveDown();

private:
    void init();

    QAction *m_moveUp;
    QAction *m_moveDown;
    int m_pageStep;
    int m_viewportMargin;
    bool m_scrollable;
};

#endif // CSCROLLABLEWIDGET_H
