#include "CHistoryWindow.h"
#include "ui_CHistoryWindow.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

#include <QScrollBar>

CHistoryWindow::CHistoryWindow(QTextDocument *history, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CHistoryWindow)
{
    ui->setupUi(this);
    ui->pteHistory->setDocument(history);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->pteHistory->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->pteHistory->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &CHistoryWindow::backTriggered);
    connect(CAutomate::getInstance(), &CAutomate::signalVariableChanged, this, &CHistoryWindow::slotVariableChanged);
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

    CAutomate *automate = CAutomate::getInstance();
    IVariable *ivar = automate->getVariable(name);

    if (!automate->getDisplayConf()->getListForScreenHistory().contains(ivar)) {
        return;
    }

    ui->pteHistory->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
}
