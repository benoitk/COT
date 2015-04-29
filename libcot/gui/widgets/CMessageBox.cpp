#include "CMessageBox.h"

#include "CToolButton.h"

#include <QLabel>

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
}
