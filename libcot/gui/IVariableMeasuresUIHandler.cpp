#include "IVariableMeasuresUIHandler.h"
#include "CScrollableWidget.h"
#include "CToolButton.h"
#include "CPCWindow.h"
#include "CMeasureWindow.h"
#include "IVariable.h"
#include "CUnit.h"

#include <QLabel>

namespace {
QString valueAndUnit(IVariable *ivar) {
    const CUnit *unit = ivar->getUnit();
    // KDAB: remove custom mg/l
    return QString("%1%2").arg(ivar->toString()).arg(unit ? unit->getLbl() : QString("mg/l"));
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
    // KDAB: Fix me - use proper way to get stream name
    row.widgetAt<CToolButton *>(0)->setUserData(ivar->getRelatedStreamName());
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
    const QString stream = button->userData().toString();
    // KDAB: Fix me when api working from customer
    CPCWindow::openModal<CMeasureWindow>(/*stream*/"");
}
