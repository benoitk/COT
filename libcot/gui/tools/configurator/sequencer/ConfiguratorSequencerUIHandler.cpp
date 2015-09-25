#include "ConfiguratorSequencerUIHandler.h"
#include "CScrollablePagerWidget.h"
#include "CPushButton.h"
#include "CToolButton.h"
#include "CClickableLabel.h"

#include <CVariableFactory.h>
#include <CAutomate.h>
#include <CScheduler.h>
#include <ICycle.h>

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

    const CyclePairList cycles = cyclePairList();
    QList<IVariable *> ivars;

    for (int i = 0; i < cycles.count(); ++i) {
        const CyclePair &pair = cycles[i];
        ICycle *cycle = pair.first;
        Q_ASSERT(cycle);
        IVariable *ivar = CVariableFactory::buildTemporary(QString::number(i), cycle->getLabel(), e_type_string);
        m_internalVariables[ivar->getName()] = ivar;
        ivars << ivar;
    }

    IConfiguratorUIHandler::layout(ivars, true);
}

ConfiguratorSequencerUIHandler::CyclePairList ConfiguratorSequencerUIHandler::cyclePairList() const
{
    CAutomate *automate = CAutomate::getInstance();
    CScheduler *scheduler = automate->getScheduler();
    return fromCycleList(scheduler->getListSequenceCyclesMesures());
}

void ConfiguratorSequencerUIHandler::setCyclePairList(const ConfiguratorSequencerUIHandler::CyclePairList &pairs)
{
    CAutomate *automate = CAutomate::getInstance();
    CScheduler *scheduler = automate->getScheduler();
    scheduler->setListSequenceCyclesMesures(fromCyclePairList(pairs), true);
}

QList<ICycle *> ConfiguratorSequencerUIHandler::fromCyclePairList(const ConfiguratorSequencerUIHandler::CyclePairList &pairs)
{
    QList<ICycle *> cycles;

    foreach (const CyclePair &pair, pairs) {
        for (int i = 0; i < pair.second; ++i) {
            cycles << pair.first;
        }
    }

    return cycles;
}

ConfiguratorSequencerUIHandler::CyclePairList ConfiguratorSequencerUIHandler::fromCycleList(const QList<ICycle *> &cycles)
{
    CyclePairList pairs;

    foreach (ICycle *cycle, cycles) {
        if (cycle->getType() != e_cycle_measure) {
            continue;
        }

        if (pairs.isEmpty() || pairs.last().first != cycle) {
            pairs << qMakePair(cycle, 1);
        }
        else {
            ++pairs.last().second;
        }
    }

    return pairs;
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
            return new CClickableLabel(QStringLiteral("X"), container());

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
    const CyclePair pair = cyclePairList().value(index);
    row.widgetAt<CPushButton *>(0)->setText(ivar->getLabel());
    applyEditorConstraints(row.widgets.value(0), ivar);
    row.widgetAt<CPushButton *>(2)->setText(QString::number(pair.second));
    applyEditorConstraints(row.widgets.value(2), ivar);
}

void ConfiguratorSequencerUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    const int index = ivar->getName().toInt();
    CyclePairList pairs = cyclePairList();
    pairs.removeAt(index);
    setCyclePairList(pairs);
    delete m_internalVariables.take(ivar->getName());
}

void ConfiguratorSequencerUIHandler::rowDeleted(const QString &name)
{
    Q_UNUSED(name);
    layout();
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
    CyclePairList pairs = cyclePairList();
    CyclePair &pair = pairs[index];
    Q_ASSERT(pair.first);
    QString cycleName = pair.first->getName();

    if (!selectCycle(cycleName) || cycleName.isEmpty()) {
        return;
    }

    ICycle *cycle = automate->getCycle(cycleName);
    Q_ASSERT(cycle);

    if (cycle->getType() != e_cycle_measure) {
        return;
    }

    pair.first = cycle;
    setCyclePairList(pairs);
}

void ConfiguratorSequencerUIHandler::slotEditValueClicked()
{
    const int index = qobject_cast<CPushButton *>(sender())->userData().toInt();
    CyclePairList pairs = cyclePairList();
    CyclePair &pair = pairs[index];
    Q_ASSERT(pair.first);
    int count = pair.second;

    if (!enterInteger(count) || count <= 0) {
        return;
    }

    pair.second = count;
    setCyclePairList(pairs);
}
