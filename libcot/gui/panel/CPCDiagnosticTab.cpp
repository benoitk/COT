#include "CPCDiagnosticTab.h"
#include "ui_CPCDiagnosticTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CPCDiagnosticTab::CPCDiagnosticTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCDiagnosticTab)
{
    ui->setupUi(this);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    m_diagnosticHandler = new IVariableUIHandler(ui->swCentral, this);
    updateDiagnostic();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayUpdated,
            this, &CPCDiagnosticTab::updateDiagnostic);
}

CPCDiagnosticTab::~CPCDiagnosticTab()
{
    delete ui;
}

CVerticalButtonBar *CPCDiagnosticTab::buttonBar() const
{
    return ui->vbbButtons;
}

void CPCDiagnosticTab::updateDiagnostic()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    IVariablePtrList screenDiagnostics = displayConf->getListForScreenDiagnostic();
    m_diagnosticHandler->layout(screenDiagnostics);
}
