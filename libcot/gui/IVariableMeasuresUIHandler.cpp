#include "IVariableMeasuresUIHandler.h"
#include "CScrollableWidget.h"
#include "CScrollablePagerWidget.h"
#include "CToolButton.h"
#include "CPCWindow.h"
#include "CMeasureWindow.h"
#include "IVariable.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"
#include "CUnit.h"
#include "StyleRepository.h"
#include "CClickableLabel.h"

#include <QDebug>
#include <CPlotObject.h>

namespace {
QString valueAndUnit(IVariable *ivar) {
    const CUnit *unit = ivar->getUnit();
    return QString("%1%2").arg(ivar->toString()).arg(unit ? unit->getLabel() : QString());
}
}

IVariableMeasuresUIHandler::IVariableMeasuresUIHandler(Flags flags, CScrollableWidget *scrollable, CAutomate* arg_automate, QObject *parent)
    : IVariableUIHandler(arg_automate, scrollable, parent)
    , m_flags(flags)
    , m_automate(arg_automate)
{
    connect(m_automate, &CAutomate::signalUpdateStateStream,
            this, &IVariableMeasuresUIHandler::slotUpdateStateStream);
}

int IVariableMeasuresUIHandler::columnCount() const
{
    return 5;
}

enum {
    POS_DETAILS = 0,
    POS_COLOR = 1,
    POS_LABEL = 2,
    POS_VALUE = 3,
    POS_ERROR = 4
};

QWidget *IVariableMeasuresUIHandler::createWidget(int index, IVariable *ivar)
{
    switch (index) {
    case POS_DETAILS:
        return (m_flags & ShowStreamButton) ? newDetailsButton(ivar) : Q_NULLPTR;

    case POS_COLOR:
        // not used anymore
        return (m_flags & ShowLegend) ? newColorLegend(ivar) : Q_NULLPTR;

    case POS_LABEL:
        return newLabel(ivar);

    case POS_VALUE:
        return newValueLabel(ivar);

    case POS_ERROR:
        return newErrorLabel(ivar);

    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void IVariableMeasuresUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(ivar);
    CToolButton *button = row.widgetAt<CToolButton *>(POS_DETAILS);
    if (button) {
        connect(button, &CToolButton::clicked,
                this, &IVariableMeasuresUIHandler::slotButtonMeasureDetailsClicked);
    }
}

void IVariableMeasuresUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    CToolButton *button = row.widgetAt<CToolButton *>(POS_DETAILS);
    if (button) {
        button->setUserData(ivar->getName());
    }
    row.widgetAt<CClickableLabel *>(POS_LABEL)->setText(ivar->getLabel());
    row.widgetAt<CClickableLabel *>(POS_VALUE)->setText(valueAndUnit(ivar));
}

QWidget *IVariableMeasuresUIHandler::newDetailsButton(IVariable *ivar)
{
    QWidget *widget;
    if (m_automate->findStreamForMeasure(ivar->getName()).second == 0) {
        widget = new CToolButton(CToolButton::MeasureDetails, container());
    } else {
        // Empty widget, so that it takes the same height as a button
        widget = new QWidget(container());
    }
    widget->setFixedSize(StyleRepository::measuresStreamButtonSize());
    return widget;
}

QWidget *IVariableMeasuresUIHandler::newColorLegend(IVariable *ivar)
{
    QPixmap pixmap(StyleRepository::measuresStreamButtonSize());
    CVariableMeasure *measureVar = ivar->getRelatedMeasure();
    Q_ASSERT(measureVar);
    if (!measureVar->color().isValid()) {
        measureVar->setColor(CPlotObject::createNewColor());
    }
    pixmap.fill(measureVar->color());
    CClickableLabel *label = new CClickableLabel(container());
    label->setPixmap(pixmap);
    return label;
}

CClickableLabel *IVariableMeasuresUIHandler::newLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CClickableLabel *label = IVariableUIHandler::newLabel(ivar);
    QPalette pal = label->palette();
    pal.setColor(label->foregroundRole(), QColor(Qt::gray));
    label->setPalette(pal);
    label->setFont(StyleRepository::measureFont());
    return label;
}

CClickableLabel *IVariableMeasuresUIHandler::newValueLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CClickableLabel *label = IVariableUIHandler::newLabel(ivar);
    label->setFont(StyleRepository::measureFont());
    return label;
}

CClickableLabel *IVariableMeasuresUIHandler::newErrorLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CClickableLabel *label = IVariableUIHandler::newLabel(ivar);
    label->setFont(StyleRepository::measureFont());
    QPalette pal = label->palette();
    pal.setColor(label->foregroundRole(), QColor(Qt::red));
    label->setPalette(pal);
    return label;
}

void IVariableMeasuresUIHandler::slotButtonMeasureDetailsClicked()
{
    const CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString measureName = button->userData().toString();
    CVariableStream *streamVar = m_automate->findStreamForMeasure(measureName).first;
    CPCWindow::openModal<CMeasureWindow>(m_automate, streamVar);

}

QString IVariableMeasuresUIHandler::textForStreamState(CAutomate::eStateStream state) const
{
    switch (state) {
    case CAutomate::STREAM_DEFAULT:
        return tr("Default");
    case CAutomate::WATER_DEFAULT:
        return tr("Water default");
    case CAutomate::ACTIVE:
    case CAutomate::INACTIVE:
        return QString(" "); // workaround for repaint bug
        break;
    }
    return QString();
}

void IVariableMeasuresUIHandler::slotUpdateStateStream(const QString &arg_streamName, CAutomate::eStateStream state)
{

    CVariableStream *stream = m_automate->getStream(arg_streamName);
    if (!stream) {
        qWarning() << "Automat error: updateStateStream emitted unknown stream name" << arg_streamName;
        return;
    }
    const QList<IVariable *> measures = stream->getListMeasures();
    if (!measures.isEmpty()) {
        CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measures.at(0));
        IVariable *var = measureVar->getMeasureVariable();
        Row* row = getRow(var->getName());
        if (row) {
            row->widgetAt<CClickableLabel *>(POS_ERROR)->setText(textForStreamState(state));
        }
    }
}
