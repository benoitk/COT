#include "IWindow.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"
#include "CToolButton.h"

#include <QGridLayout>
#include <QAction>

IWindow::IWindow(QWidget *parent) :
    QWidget(parent)
{
    m_scrollableWidget = new CScrollableWidget(this);

    m_buttonBar = new CVerticalButtonBar(this);
    m_buttonBar->addAction(CToolButton::ScrollUp, m_scrollableWidget->moveUp());
    m_buttonBar->addAction(CToolButton::ScrollDown, m_scrollableWidget->moveDown());
    QAction *returnAction = m_buttonBar->addAction(CToolButton::Back);
    connect(returnAction, SIGNAL(triggered()), this, SLOT(hide()));

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(m_scrollableWidget, 1, 0);
    gridLayout->addWidget(m_buttonBar, 1, 1);
}

void IWindow::setMainWidget(QWidget *widget)
{
    if (!widget) {
        return;
    }
    m_scrollableWidget->setWidget(widget);
}

QWidget *IWindow::mainWidget()
{
    return m_scrollableWidget->widget();
}

CVerticalButtonBar *IWindow::buttonBar()
{
    return m_buttonBar;
}

CScrollableWidget *IWindow::scrollable()
{
    return m_scrollableWidget;
}

