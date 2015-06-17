#include "CPCHistogramTab.h"
#include "ui_CPCHistogramTab.h"

#include <CAutomate.h>
#include <CVariableMeasure.h>
#include <CVariableStream.h>
#include <CPlotObject.h>

CPCHistogramTab::CPCHistogramTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCHistogramTab)
    , m_currentCurveNumber(0)
{
    ui->setupUi(this);

    connect(ui->vbbButtons->addAction(CToolButton::ScrollUp), &QAction::triggered,
            this, &CPCHistogramTab::moveUp);
    connect(ui->vbbButtons->addAction(CToolButton::ScrollDown), &QAction::triggered,
            this, &CPCHistogramTab::moveDown);

    CAutomate *automate = CAutomate::getInstance();
    connect(automate, &CAutomate::signalUpdatePlotting,
            this, &CPCHistogramTab::slotUpdatePlotting);

    updateCurves();
}

CPCHistogramTab::~CPCHistogramTab()
{
    delete ui;
}

CVerticalButtonBar *CPCHistogramTab::buttonBar() const
{
    return ui->vbbButtons;
}

void CPCHistogramTab::moveUp()
{
    showCurve(qMax(m_currentCurveNumber - 1, 0));
}

void CPCHistogramTab::moveDown()
{
    showCurve(qMin(m_currentCurveNumber + 1, m_plots.count() - 1));
}

void CPCHistogramTab::slotUpdatePlotting()
{
    const QList<CVariableMeasure *> measures = allMeasures();
    for (int i = 0 ; i < measures.count() ; ++i) {
        CVariableMeasure *measureVar = measures.at(i);
        const float value = measureVar->toFloat();
        ui->graphicsWidget->addPoint(value, m_plots.at(i));
    }
    ui->graphicsWidget->doneUpdatingPlotting();
}

void CPCHistogramTab::updateCurves()
{
    const QList<CVariableMeasure *> measures = allMeasures();
    if (m_plots.count() != measures.count()) {
        qDeleteAll(m_plots);
        m_plots.clear();
        // Need one CPlotObject per measure, to store the values as they come in,
        // even if we only display one (or a few) at a time.
        for (int i = 0 ; i < measures.count() ; ++i) {
            CPlotObject *plot = new CPlotObject;
            m_plots.append(plot);
        }
    }

    showCurve(qMin(m_currentCurveNumber, measures.count() - 1));
}

void CPCHistogramTab::showCurve(int num)
{
    m_currentCurveNumber = num;
    ui->graphicsWidget->showPlotObject(m_plots.at(num));
}

QList<CVariableMeasure *> CPCHistogramTab::allMeasures() // could maybe be API in CAutomate.
{
    QList<CVariableMeasure *> ret;
    CAutomate *automate = CAutomate::getInstance();
    const QList<CVariableStream*> streams = automate->getListStreams();
    foreach (CVariableStream *streamVar, streams) {
        foreach (IVariable *measure, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);
            ret.append(measureVar);
        }
    }
    return ret;
}
