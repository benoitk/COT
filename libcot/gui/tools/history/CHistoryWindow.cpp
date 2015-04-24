#include "CHistoryWindow.h"
#include "ui_CHistoryWindow.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CHistoryWindow::CHistoryWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CHistoryWindow)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());
    connect(ui->vbbButtons->addAction(CToolButton::Back), &QAction::triggered,
            this, &CHistoryWindow::backTriggered);

    m_historyHandler = new IVariableUIHandler(ui->swCentral, this);
    updateHistory();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayConfChanged,
            this, &CHistoryWindow::updateHistory);
}

CHistoryWindow::~CHistoryWindow()
{
    delete ui;
}

void CHistoryWindow::backTriggered()
{
    close();
}

void CHistoryWindow::updateHistory()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    IVariablePtrList screenHistory = displayConf->getListForScreenHistory();
    m_historyHandler->layout(screenHistory);
}
