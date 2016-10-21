#include "CPCDiagnosticTab.h"
#include "ui_CPCDiagnosticTab.h"

#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

CPCDiagnosticTab::CPCDiagnosticTab(CAutomate* arg_automate, QWidget *parent)
    : IPCTab(arg_automate, parent)
    , ui(new Ui::CPCDiagnosticTab)
{
    ui->setupUi(this);
    ui->swStatus->setupStatusWidget(m_automate);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    m_diagnosticHandler = new IVariableUIHandler(m_automate, ui->swCentral, this);
    updateDiagnostic();
    connect(m_automate, &CAutomate::signalDisplayUpdated,
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
    CDisplayConf *displayConf = m_automate->getDisplayConf();
    IVariablePtrList screenDiagnostics = displayConf->getListForScreenDiagnostic();
    m_diagnosticHandler->layout(screenDiagnostics);
}
