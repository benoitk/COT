#include "CDialogMaintenance.h"

#include "CVerticalButtonBar.h"
#include "IVariableUIHandler.h"
#include "CScrollableWidget.h"
#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QPainter>
#include <QDebug>

CDialogMaintenance::CDialogMaintenance(QWidget *parent)
    : QDialog(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);

    m_tabWidget = new QTabWidget(this);
    QWidget *page = new QWidget(m_tabWidget);
    m_tabWidget->addTab(page, QString(QStringLiteral("no_label")) /* let's hope setTitle will be called! */);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
    setLayout(mainLayout);

    m_buttonBar = new CVerticalButtonBar(page);
    CScrollableWidget* swWidget = new CScrollableWidget(this);
    m_buttonBar->addAction(CToolButton::ScrollUp, swWidget->moveUp());
    m_buttonBar->addAction(CToolButton::ScrollDown, swWidget->moveDown());

    connect(m_buttonBar->addAction(CToolButton::Ok), &QAction::triggered, this, &CDialogMaintenance::accept);
    connect(m_buttonBar->addAction(CToolButton::Back), &QAction::triggered, this, &CDialogMaintenance::reject);

    QVBoxLayout* leftLayout  =new QVBoxLayout;
    m_errorLabel = new QLabel(page);
    m_calibValueHandler = new IVariableUIHandler(swWidget, page);
    leftLayout->addWidget(swWidget);
    leftLayout->addWidget(m_errorLabel);

    QHBoxLayout * pageLayout = new QHBoxLayout(page);
    pageLayout->addLayout(leftLayout);
    pageLayout->addWidget(m_buttonBar);
}

void CDialogMaintenance::slotUpdateLayout(QList<IVariable*> arg_listIVariables)
{
    m_calibValueHandler->layout(arg_listIVariables);
    repaint();
}

void CDialogMaintenance::setTitle(const QString &title)
{
    m_tabWidget->setTabText(0, title);
}
void CDialogMaintenance::slotUpdateError(const QString& arg_error){
    m_errorLabel->setText(arg_error);
}


void CDialogMaintenance::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.setPen(palette().color(QPalette::WindowText));
    p.setBrush(palette().brush(QPalette::Window));
    p.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 7, 7);

    QDialog::paintEvent(event);
}
