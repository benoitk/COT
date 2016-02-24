#include "CDialogConfirmation.h"

#include "CVerticalButtonBar.h"
#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QPainter>
#include <QDebug>

CDialogConfirmation::CDialogConfirmation(const QString& arg_message, QWidget *parent)
    : CDialog(parent)
{
    connect(m_buttonBar->addAction(CToolButton::Ok), &QAction::triggered, this, &CDialogConfirmation::accept);
    connect(m_buttonBar->addAction(CToolButton::Back), &QAction::triggered, this, &CDialogConfirmation::reject);


    m_confirmationMessage = new QLabel(arg_message);

    setTitle(tr("Attention"));
    setMainWidget(m_confirmationMessage);


}



void CDialogConfirmation::setConfirmationMessage(const QString &message)
{
    m_confirmationMessage->setText(message);
}
