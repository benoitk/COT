#include "IScrollablePlainTextEdit.h"
#include "CScrollablePlainTextEdit.h"
#include "CVerticalButtonBar.h"

#include <QHBoxLayout>

IScrollablePlainTextEdit::IScrollablePlainTextEdit(QWidget *parent)
    : QWidget(parent)
    , m_scrollableWidget(new CScrollablePlainTextEdit(this))
    , m_verticalButtonBar(new CVerticalButtonBar(this))
{
    QHBoxLayout *hl = new QHBoxLayout(this);
    hl->addWidget(m_scrollableWidget);
    hl->addWidget(m_verticalButtonBar);
}

IScrollablePlainTextEdit::~IScrollablePlainTextEdit()
{
}

CScrollablePlainTextEdit *IScrollablePlainTextEdit::scrollableWidget() const
{
    return m_scrollableWidget;
}

CVerticalButtonBar *IScrollablePlainTextEdit::buttonBar() const
{
    return m_verticalButtonBar;
}
