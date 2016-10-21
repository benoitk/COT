#include "CHistoryWindow.h"
#include "ui_CHistoryWindow.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

#include <QScrollBar>

CHistoryWindow::CHistoryWindow(CAutomate* arg_automate,QTextDocument *document, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CHistoryWindow)
    , m_automate(arg_automate)
{
    ui->setupUi(this);
    ui->pteHistory->setDocument(document);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->pteHistory->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->pteHistory->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &CHistoryWindow::backTriggered);
    connect(m_automate, &CAutomate::signalVariableChanged, this, &CHistoryWindow::slotVariableChanged);
}

CHistoryWindow::~CHistoryWindow()
{
    delete ui;
}

void CHistoryWindow::backTriggered()
{
    close();
}

void CHistoryWindow::slotVariableChanged(const QString &name)
{
    // The QTextDocument is modified by CPCToolsTab::slotVariableChanged
    // All we have to do here is scroll down.

    IVariable *ivar = m_automate->getVariable(name);

    if (!m_automate->getDisplayConf()->getListForScreenHistory().contains(ivar)) {
        return;
    }

    ui->pteHistory->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
}
