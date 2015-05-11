#include "IVariableMeasuresUIHandler.h"
#include "CScrollableWidget.h"
#include "CToolButton.h"
#include "CPCWindow.h"
#include "CMeasureWindow.h"
#include "CAutomate.h"
#include "IVariable.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"
#include "CUnit.h"

#include <QLabel>

namespace {
QString valueAndUnit(IVariable *ivar) {
    const CUnit *unit = ivar->getUnit();
    return QString("%1%2").arg(ivar->toString()).arg(unit ? unit->getLbl() : QString());
}

IVariable *findMeasureStream(const QString &measureName) {
    CAutomate *automate = CAutomate::getInstance();

    foreach (IVariable *stream, automate->getMapStreams().values()) {
        CVariableStream *streamVar = static_cast<CVariableStream *>(stream);

        foreach (IVariable *measure, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measure);
            IVariable *measureMeasureVariable = measureVar->getMeasureVariable();

            if (measureMeasureVariable && measureMeasureVariable->getName() == measureName) {
                return stream;
            }
        }
    }

    return Q_NULLPTR;
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
            return newEditor(ivar);

        case 1:
            return newLabel(ivar);

        case 2:
            return newUnit(ivar);
    }

    Q_ASSERT(false);
    return Q_NULLPTR;
}

void IVariableMeasuresUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(ivar);
    connect(row.widgetAt<CToolButton *>(0), &CToolButton::clicked,
            this, &IVariableMeasuresUIHandler::slotButtonMeasureDetailsClicked);
}

void IVariableMeasuresUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    row.widgetAt<QLabel *>(1)->setText(ivar->getLabel());
    row.widgetAt<CToolButton *>(0)->setUserData(ivar->getName());
    row.widgetAt<QLabel *>(2)->setText(valueAndUnit(ivar));
}

QWidget *IVariableMeasuresUIHandler::newEditor(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CToolButton *button = new CToolButton(CToolButton::MeasureDetails, m_container);
    button->setFixedSize(30, 30);
    return button;
}

QLabel *IVariableMeasuresUIHandler::newLabel(IVariable *ivar)
{
    Q_UNUSED(ivar);
    QLabel *label = new QLabel(m_container);
    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QPalette pal = label->palette();
    pal.setColor(label->foregroundRole(), QColor(Qt::gray));
    label->setPalette(pal);
    return label;
}

QLabel *IVariableMeasuresUIHandler::newUnit(IVariable *ivar)
{
    Q_UNUSED(ivar);
    QLabel *label = new QLabel(m_container);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    return label;
}

void IVariableMeasuresUIHandler::slotButtonMeasureDetailsClicked()
{
    const CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString measureName = button->userData().toString();
    IVariable *streamVar = findMeasureStream(measureName);
    CPCWindow::openModal<CMeasureWindow>(streamVar);
}
