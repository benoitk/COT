#include "CPCHistogramTab.h"
#include "ui_CPCHistogramTab.h"

#include <CAutomate.h>
#include <CVariableMeasure.h>
#include <CVariableStream.h>
#include <CPlotObject.h>
#include <IVariableMeasuresUIHandler.h>
#include <qdebug.h>

CPCHistogramTab::CPCHistogramTab(CAutomate* arg_automate, QWidget *parent)
    : IPCTab(arg_automate, parent)
    , ui(new Ui::CPCHistogramTab)
    , m_currentCurveNumber(0)
{
    ui->setupUi(this);
    m_measuresHandler = new IVariableMeasuresUIHandler(IVariableMeasuresUIHandler::NoFlags, ui->swCentral,m_automate, this);
    ui->swCentral->setScrollable(false);

    connect(ui->vbbButtons->addAction(CToolButton::ScrollUp), &QAction::triggered,
            this, &CPCHistogramTab::moveUp);
    connect(ui->vbbButtons->addAction(CToolButton::ScrollDown), &QAction::triggered,
            this, &CPCHistogramTab::moveDown);


    connect(m_automate, &CAutomate::signalUpdatePlotting,
            this, &CPCHistogramTab::slotUpdatePlotting);

    updateCurves();
}

CPCHistogramTab::~CPCHistogramTab()
{
    // qDeleteAll(m_plots); // requires KPlotWidget::setAutoDelete(false), @since KF 5.12
    delete ui;
}

CVerticalButtonBar *CPCHistogramTab::buttonBar() const
{
    return ui->vbbButtons;
}

void CPCHistogramTab::moveUp()
{
    showCurve(qMax(m_currentCurveNumber - 1, 0));
    updateActions();
}

void CPCHistogramTab::moveDown()
{
    showCurve(qMin(m_currentCurveNumber + 1, m_plots.count() - 1));
    updateActions();
}

void CPCHistogramTab::slotUpdatePlotting()
{
    const QList<CVariableMeasure *> measures = m_automate->allMeasures();
    for (int i = 0 ; i < measures.count() ; ++i) {
        CVariableMeasure *measureVar = measures.at(i);
        const float value = measureVar->toFloat();
        ui->graphicsWidget->addPoint(value, m_plots.at(i), measureVar->getMeasureMin()->toFloat(), measureVar->getMeasureMax()->toFloat());
    }
    ui->graphicsWidget->doneUpdatingPlotting();
}

void CPCHistogramTab::updateCurves()
{
    const QList<CVariableMeasure *> measures = m_automate->allMeasures();

    if (m_plots.count() != measures.count()) {
        qDeleteAll(m_plots);
        m_plots.clear();
        // Need one CPlotObject per measure, to store the values as they come in,
        // even if we only display one (or a few) at a time.
        for (int i = 0 ; i < measures.count() ; ++i) {
            CVariableMeasure *measureVar = measures.at(i);
            if (!measureVar->color().isValid()) {
                measureVar->setColor(CPlotObject::createNewColor());
            }
            CPlotObject *plot = new CPlotObject(measureVar->color());
            m_plots.append(plot);
        }
    }

    showCurve(qMin(m_currentCurveNumber, measures.count() - 1));
    updateActions();
}

void CPCHistogramTab::updateActions()
{
    ui->vbbButtons->action(CToolButton::ScrollUp)->setEnabled(m_currentCurveNumber > 0);
    ui->vbbButtons->action(CToolButton::ScrollDown)->setEnabled(m_currentCurveNumber < m_plots.count() - 1);
}

void CPCHistogramTab::showCurve(int num)
{

    m_currentCurveNumber = num;
    if(m_plots.count()>num && num > -1){
        ui->graphicsWidget->showPlotObject(m_plots.at(num));
        const QList<CVariableMeasure *> measures = m_automate->allMeasures();
        IVariable *variable = measures.at(num)->getMeasureVariable();
        Q_ASSERT(variable);
        m_measuresHandler->layout(QList<IVariable *>() << variable);
    }
    else
        qDebug() << "Numéro de courbe inccorect";
}

