#include "CMeasureWindow.h"
#include "ui_CMeasureWindow.h"
#include "CMeasureStreamTab.h"
#include "CMeasureMeasureTab.h"
#include "CAutomate.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"

CMeasureWindow::CMeasureWindow(IVariablePtr stream, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CMeasureWindow)
{
    Q_ASSERT(stream);

    ui->setupUi(this);

    CVariableStream *streamVar = static_cast<CVariableStream *>(stream);

    addTab(new CMeasureStreamTab(streamVar->getListVariables(), this), streamVar->getLabel().toUpper());

    foreach (IVariable *measure, streamVar->getListMeasures()) {
        CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);
        IVariablePtrList ivars = measureVar->getListVariables();
        ivars.prepend(measureVar->getMeasureVariable());
        addTab(new CMeasureMeasureTab(ivars, this), measureVar->getLabel().toUpper());
    }
}

CMeasureWindow::~CMeasureWindow()
{

}

void CMeasureWindow::backTriggered()
{
    close();
}

void CMeasureWindow::addTab(IMeasureTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IMeasureTab::backTriggered, this, &CMeasureWindow::backTriggered);
}
