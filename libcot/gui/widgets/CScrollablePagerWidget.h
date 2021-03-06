#ifndef CSCROLLABLEPAGERWIDGET_H
#define CSCROLLABLEPAGERWIDGET_H

#include <QWidget>
#include "cot_global.h"
/*
 * This class acts as a pager for CScrollableWidget.
 * It tries to have a height proportional to its hoster height
 * so that when scrolling to the last page, it doesn't get truncated.
*/
class LIBCOT_EXPORT CScrollablePagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CScrollablePagerWidget(QWidget *parent = 0);
    virtual ~CScrollablePagerWidget();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    // hostHeight = the height of the CScrollableWidget viewport
    void setHostHeight(int hostHeight);

    // pageHeight = height of an integer number of items, usually a bit smaller than hostHeight
    void setPageHeight(int pageHeight);

    int numPages() const;

private:
    int m_hostHeight;
    int m_pageHeight;
};

#endif // CSCROLLABLEPAGERWIDGET_H
