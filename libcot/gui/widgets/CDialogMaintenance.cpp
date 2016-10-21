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

CDialogMaintenance::CDialogMaintenance(CAutomate* arg_automate, QWidget *parent)
    : QDialog(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setMinimumWidth(500);
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
    m_errorLabel->setStyleSheet("QLabel { color : red; }");
    m_calibValueHandler = new IVariableUIHandler(arg_automate, swWidget, page);
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
void CDialogMaintenance::setDisabledValidationButton(bool arg_disabled){
    m_buttonBar->button(CToolButton::Ok)->setDisabled(arg_disabled);
}

void CDialogMaintenance::setTitle(const QString &title)
{
    m_tabWidget->setTabText(0, title);
}
void CDialogMaintenance::setErrors(QList<IVariable*> arg_listIVariable){
    QString sErrors;
    foreach (IVariable* var, arg_listIVariable) {
        if(var->toBool() == true)
            sErrors += var->getLabel() + "  ";
    }
    m_errorLabel->setText(sErrors);

}


void CDialogMaintenance::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.setPen(palette().color(QPalette::WindowText));
    p.setBrush(palette().brush(QPalette::Window));
    p.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 7, 7);

    QDialog::paintEvent(event);
}
