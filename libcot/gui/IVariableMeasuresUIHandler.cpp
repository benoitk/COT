#include "IVariableMeasuresUIHandler.h"
#include "CScrollableWidget.h"
#include "CScrollablePagerWidget.h"
#include "CToolButton.h"
#include "CPCWindow.h"
#include "CMeasureWindow.h"
#include "CAutomate.h"
#include "IVariable.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"
#include "CUnit.h"
#include "StyleRepository.h"

#include <QLabel>
#include <QDebug>

namespace {
QString valueAndUnit(IVariable *ivar) {
    const CUnit *unit = ivar->getUnit();
    return QString("%1%2").arg(ivar->toString()).arg(unit ? unit->getLabel() : QString());
}

QPair<CVariableStream *, int> findStreamForMeasure(const QString &measureName) {
    CAutomate *automate = CAutomate::getInstance();

    foreach ( CVariableStream *streamVar, automate->getListStreams()) {

        const QList<IVariable *> measures = streamVar->getListMeasures();
        for (int i = 0 ; i < measures.count(); ++i) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measures.at(i));
            IVariable *measureMeasureVariable = measureVar->getMeasureVariable();

            if (measureMeasureVariable && measureMeasureVariable->getName() == measureName) {
                return qMakePair<CVariableStream *,int >(streamVar, i);
            }
        }
    }

    qWarning() << "Stream not found for measure" << measureName;
    return qMakePair<CVariableStream *,int >(Q_NULLPTR, -1);
}

}

IVariableMeasuresUIHandler::IVariableMeasuresUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IVariableUIHandler(scrollable, parent)
{
}

int IVariableMeasuresUIHandler::columnCount() const
{
    return 3;
}

QWidget *IVariableMeasuresUIHandler::createWidget(int index, IVariable *ivar)
{
    switch (index) {
        case 0:
            return newDetailsButton(ivar);

        case 1:
            return newLabel(ivar);

        case 2:
            return newValueLabel(ivar);
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void IVariableMeasuresUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(ivar);
    CToolButton *button = row.widgetAt<CToolButton *>(0);
    if (button) {
        connect(button, &CToolButton::clicked,
                this, &IVariableMeasuresUIHandler::slotButtonMeasureDetailsClicked);
    }
}

void IVariableMeasuresUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    CToolButton *button = row.widgetAt<CToolButton *>(0);
    if (button) {
        button->setUserData(ivar->getName());
    }
    row.widgetAt<QLabel *>(1)->setText(ivar->getLabel());
    row.widgetAt<QLabel *>(2)->setText(valueAndUnit(ivar));
}

QWidget *IVariableMeasuresUIHandler::newDetailsButton(IVariable *ivar)
{
    QWidget *widget;
    if (findStreamForMeasure(ivar->getName()).second == 0) {
        widget = new CToolButton(CToolButton::MeasureDetails, container());
    } else {
        // Empty widget, so that it takes the same height as a button
        widget = new QWidget(container());
    }
    widget->setFixedSize(StyleRepository::measuresStreamButtonSize());
    return widget;
}

QLabel *IVariableMeasuresUIHandler::newLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    QLabel *label = new QLabel(container());
    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QPalette pal = label->palette();
    pal.setColor(label->foregroundRole(), QColor(Qt::gray));
    label->setPalette(pal);
    label->setFont(StyleRepository::measureFont());
    return label;
}

QLabel *IVariableMeasuresUIHandler::newValueLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    QLabel *label = new QLabel(container());
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    label->setFont(StyleRepository::measureFont());
    return label;
}

void IVariableMeasuresUIHandler::slotButtonMeasureDetailsClicked()
{
    const CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString measureName = button->userData().toString();
    CVariableStream *streamVar = findStreamForMeasure(measureName).first;
    CPCWindow::openModal<CMeasureWindow>(streamVar);
}
