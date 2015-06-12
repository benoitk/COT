#include "CMessageBox.h"
#include "CVerticalButtonBar.h"

#include <QAction>
#include <QLabel>

CMessageBox::CMessageBox(const QString &message, QWidget *parent)
    : CDialog(tr("INFORMATION"), parent)
{
    QLabel *label = new QLabel(this);
    label->setText(message);
    setMainWidget(label);

    QAction *okAction = buttonBar()->addAction(CToolButton::Ok);
    connect(okAction, &QAction::triggered, this, &QWidget::close);
}

CMessageBox::~CMessageBox()
{

}
