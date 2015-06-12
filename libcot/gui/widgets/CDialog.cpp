#include "CDialog.h"
#include "CVerticalButtonBar.h"

#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QPainter>
#include <QDebug>

CDialog::CDialog(QWidget *parent)
    : QDialog(parent)
{
    m_tabWidget = new QTabWidget(this);
    QWidget *page = new QWidget(m_tabWidget);
    m_tabWidget->addTab(page, QString() /* let's hope setTitle will be called! */);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);

    m_buttonBar = new CVerticalButtonBar(page);

    m_pageLayout = new QHBoxLayout(page);
    m_pageLayout->addWidget(m_buttonBar);
}

CDialog::~CDialog()
{

}

void CDialog::setTitle(const QString &title)
{
    m_tabWidget->setTabText(0, title);
}

void CDialog::setMainWidget(QWidget *widget)
{
    m_pageLayout->insertWidget(0, widget, Qt::AlignTop);
}

void CDialog::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 7, 7);

    QDialog::paintEvent(event);
}

CVerticalButtonBar *CDialog::buttonBar() const
{
    return m_buttonBar;
}
