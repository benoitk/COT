#include "CMessageBox.h"
#include "CVerticalButtonBar.h"

#include <QLabel>
#include <QAction>
#include <QHBoxLayout>

CMessageBox::CMessageBox(const QString &message, QWidget *parent)
    : QDialog(parent),
      m_message(message)
{
    QLabel *label = new QLabel(this);
    label->setText(m_message);

    m_buttonBar = new CVerticalButtonBar(this);
    QAction *okAction = m_buttonBar->addAction(CToolButton::Ok);
    connect(okAction, &QAction::triggered, this, &QWidget::close);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(label);
    hLayout->addWidget(m_buttonBar);

    setProperty("modalStyle", true); // see cot.qss
}

CMessageBox::~CMessageBox()
{

}
