#include "CDialog.h"
#include "CVerticalButtonBar.h"

#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include <QTabWidget>

CDialog::CDialog(const QString &title, QWidget *parent)
    : QDialog(parent)
{
    QTabWidget *tabWidget = new QTabWidget(this);
    QWidget *page = new QWidget(tabWidget);
    tabWidget->addTab(page, title);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(tabWidget);

    m_buttonBar = new CVerticalButtonBar(page);

    m_pageLayout = new QHBoxLayout(page);
    m_pageLayout->addWidget(m_buttonBar);

    setProperty("modalStyle", true); // see cot.qss
}

CDialog::~CDialog()
{

}

void CDialog::setMainWidget(QWidget *widget)
{
    m_pageLayout->insertWidget(0, widget);
}

CVerticalButtonBar *CDialog::buttonBar() const
{
    return m_buttonBar;
}
