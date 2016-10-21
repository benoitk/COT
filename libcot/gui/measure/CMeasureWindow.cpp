#include "CMeasureWindow.h"
#include "ui_CMeasureWindow.h"
#include "CMeasureStreamTab.h"
#include "CMeasureMeasureTab.h"
#include "CAutomate.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"

CMeasureWindow::CMeasureWindow(CAutomate* arg_automate, CVariableStream *stream, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CMeasureWindow)
    , m_automate(arg_automate)
{
    Q_ASSERT(stream);

    ui->setupUi(this);

    addTab(new CMeasureStreamTab(arg_automate, stream->getListVariables(), this), stream->getLabel().toUpper());

    foreach (IVariable *measure, stream->getListMeasures()) {
        CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);
        IVariablePtrList ivars = measureVar->getListVariables();
        ivars.prepend(measureVar->getMeasureVariable());
        addTab(new CMeasureMeasureTab(m_automate, ivars, this), measureVar->getLabel().toUpper());
    }
}

CMeasureWindow::~CMeasureWindow()
{

}

void CMeasureWindow::backTriggered()
{
    m_automate->slotSerializeAndSave();
    close();
}

void CMeasureWindow::addTab(IMeasureTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IMeasureTab::backTriggered, this, &CMeasureWindow::backTriggered);
}
