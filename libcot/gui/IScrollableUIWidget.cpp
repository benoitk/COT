#include "IScrollableUIWidget.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"

#include <QHBoxLayout>

IScrollableUIWidget::IScrollableUIWidget(QWidget *parent)
    : QWidget(parent)
    , m_scrollableWidget(new CScrollableWidget(this))
    , m_verticalButtonBar(new CVerticalButtonBar(this))
{
    QHBoxLayout *hl = new QHBoxLayout(this);
    hl->addWidget(m_scrollableWidget);
    hl->addWidget(m_verticalButtonBar);
}

IScrollableUIWidget::~IScrollableUIWidget()
{
}

CScrollableWidget *IScrollableUIWidget::scrollableWidget() const
{
    return m_scrollableWidget;
}

CVerticalButtonBar *IScrollableUIWidget::buttonBar() const
{
    return m_verticalButtonBar;
}
