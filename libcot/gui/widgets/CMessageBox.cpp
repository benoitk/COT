#include "CMessageBox.h"
#include "CToolButton.h"
#include "CVerticalButtonBar.h"

#include <QLabel>
#include <QAction>

CMessageBox::CMessageBox(const QString &message, QWidget *parent)
    : IWindow(parent),
      m_message(message)
{
    setupWindow();
}

CMessageBox::~CMessageBox()
{

}

void CMessageBox::setupWindow()
{
    QLabel *label = new QLabel(this);
    label->setText(m_message);

    setMainWidget(label);

    QAction *okAction = buttonBar()->addAction(CToolButton::Ok);
    buttonBar()->removeAction(CToolButton::Back);
    connect(okAction, &QAction::triggered, this, &QWidget::close);
}
