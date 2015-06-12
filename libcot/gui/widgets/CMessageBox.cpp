#include "CMessageBox.h"
#include "CVerticalButtonBar.h"

#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include <QTabWidget>

CMessageBox::CMessageBox(const QString &message, QWidget *parent)
    : QDialog(parent),
      m_message(message)
{
    QTabWidget *tabWidget = new QTabWidget(this);
    QWidget *page = new QWidget(tabWidget);
    tabWidget->addTab(page, tr("INFORMATION"));
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(tabWidget);

    QLabel *label = new QLabel(page);
    label->setText(m_message);

    m_buttonBar = new CVerticalButtonBar(page);
    QAction *okAction = m_buttonBar->addAction(CToolButton::Ok);
    connect(okAction, &QAction::triggered, this, &QWidget::close);

    QHBoxLayout *pageLayout = new QHBoxLayout(page);
    pageLayout->addWidget(label);
    pageLayout->addWidget(m_buttonBar);

    setProperty("modalStyle", true); // see cot.qss
}

CMessageBox::~CMessageBox()
{

}
