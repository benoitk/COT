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

QWidget *IVariableMeasuresUIHandler::newEditor(IVariable *ivar)
{
    Q_UNUSED(ivar);
    CToolButton *button = new CToolButton(CToolButton::MeasureDetails, m_container);
    button->setFixedSize(30, 30);
    return button;
}

QLabel *IVariableMeasuresUIHandler::newUnit(IVariable *ivar)
{
    Q_UNUSED(ivar);
    QLabel *label = new QLabel(m_container);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    return label;
}

int IVariableMeasuresUIHandler::labelColumn() const
{
    return 1;
}

int IVariableMeasuresUIHandler::editorColumn() const
{
    return 0;
}

int IVariableMeasuresUIHandler::unitColumn() const
{
    return 2;
}

void IVariableMeasuresUIHandler::rowInserted(const IVariableUIHandler::Row &row)
{
    connect(qobject_cast<CToolButton *>(row.editor), &CToolButton::clicked,
            this, &IVariableMeasuresUIHandler::slotButtonMeasureDetailsClicked);
}

void IVariableMeasuresUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    row.label->setText(ivar->getLabel());
    // KDAB: Fix me - use proper way to get stream name
    qobject_cast<CToolButton *>(row.editor)->setUserData(ivar->getRelatedStreamName());
    row.unit->setText(valueAndUnit(ivar));
}

void IVariableMeasuresUIHandler::slotButtonMeasureDetailsClicked()
{
    const CToolButton *button = qobject_cast<CToolButton *>(sender());
    const QString stream = button->userData().toString();
    // KDAB: Fix me when api working from customer
    CPCWindow::openModal<CMeasureWindow>(/*stream*/"");
}
