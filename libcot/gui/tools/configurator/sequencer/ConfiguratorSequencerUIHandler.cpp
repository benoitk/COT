#include "ConfiguratorSequencerUIHandler.h"
#include "CScrollablePagerWidget.h"
#include "CPushButton.h"
#include "CToolButton.h"

#include <CVariableFactory.h>
#include <CAutomate.h>
#include <CScheduler.h>
#include <ICycle.h>

#include <QLabel>

ConfiguratorSequencerUIHandler::ConfiguratorSequencerUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
}

ConfiguratorSequencerUIHandler::~ConfiguratorSequencerUIHandler()
{
    CVariableFactory::deleteVariables(m_internalVariables);
}

void ConfiguratorSequencerUIHandler::layout()
{
    CVariableFactory::deleteVariables(m_internalVariables);

    const QList<CScheduler::CyclePair> cycles = CScheduler::getInstance()->getCycles();
    QList<IVariable *> ivars;

    for (int i = 0; i < cycles.count(); ++i) {
        const CScheduler::CyclePair &pair = cycles[i];
        ICycle *cycle = pair.first;
        Q_ASSERT(cycle);
        IVariable *ivar = CVariableFactory::buildTemporary(QString::number(i), cycle->getLabel(), type_string);
        m_internalVariables[ivar->getName()] = ivar;
        ivars << ivar;
    }

    IConfiguratorUIHandler::layout(ivars, true);
}

IVariable *ConfiguratorSequencerUIHandler::getVariable(const QString &name) const
{
    IVariable *ivar = m_internalVariables.value(name);

    if (!ivar) {
        ivar = IConfiguratorUIHandler::getVariable(name);
    }

    return ivar;
}

int ConfiguratorSequencerUIHandler::columnCount() const
{
    return 4;
}

QWidget *ConfiguratorSequencerUIHandler::createWidget(int column, IVariable *ivar)
{
    switch (column) {
        case 0:
            return newCycleButton(ivar);

        case 1:
            return new QLabel(QStringLiteral("X"), container());

        case 2:
            return newValueButton(ivar);

        case 3:
            return newDeleteButton(ivar);
    }

    return Q_NULLPTR;
}

void ConfiguratorSequencerUIHandler::rowInserted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void ConfiguratorSequencerUIHandler::rowChanged(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    const int index = ivar->getName().toInt();
    const CScheduler::CyclePair pair = CScheduler::getInstance()->getCycleAt(index);
    row.widgetAt<CPushButton *>(0)->setText(ivar->getLabel());
    applyEditorConstraints(row.widgets.value(0), ivar);
    row.widgetAt<CPushButton *>(2)->setText(QString::number(pair.second));
    applyEditorConstraints(row.widgets.value(2), ivar);
}

void ConfiguratorSequencerUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    const int index = ivar->getName().toInt();
    CScheduler *sequencer = CScheduler::getInstance();
    sequencer->removeCycleMeasureAt(index);
    delete m_internalVariables.take(ivar->getName());
}

void ConfiguratorSequencerUIHandler::rowDeleted(const QString &name)
{
    Q_UNUSED(name);
}

CPushButton *ConfiguratorSequencerUIHandler::newCycleButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    button->setUserData(ivar->getName());
    connect(button, &CPushButton::clicked, this, &ConfiguratorSequencerUIHandler::slotEditCycleClicked);
    return button;
}

CPushButton *ConfiguratorSequencerUIHandler::newValueButton(IVariable *ivar)
{
    CPushButton *button = new CPushButton(container());
    button->setUserData(ivar->getName());
    connect(button, &CPushButton::clicked, this, &ConfiguratorSequencerUIHandler::slotEditValueClicked);
    return button;
}

void ConfiguratorSequencerUIHandler::slotEditCycleClicked()
{
    const int index = qobject_cast<CPushButton *>(sender())->userData().toInt();
    CAutomate *automate = CAutomate::getInstance();
    CScheduler *sequencer = CScheduler::getInstance();
    CScheduler::CyclePair pair = sequencer->getCycleAt(index);
    Q_ASSERT(pair.first);
    QString cycleName = pair.first->getName();

    if (!selectCycle(cycleName) || cycleName.isEmpty()) {
        return;
    }

    pair.first = automate->getCycle(cycleName);
    Q_ASSERT(pair.first);
    sequencer->replaceCycleAt(index, pair);
}

void ConfiguratorSequencerUIHandler::slotEditValueClicked()
{
    const int index = qobject_cast<CPushButton *>(sender())->userData().toInt();
    CScheduler *sequencer = CScheduler::getInstance();
    CScheduler::CyclePair pair = sequencer->getCycleAt(index);
    Q_ASSERT(pair.first);
    int value = pair.second;

    if (!enterInteger(value) || value <= 0) {
        return;
    }

    pair.second = value;
    sequencer->replaceCycleAt(index, pair);
}
