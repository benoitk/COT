#include "ConfiguratorSequencerUIHandler.h"
#include "CPushButton.h"
#include "CToolButton.h"

#include <CVariableFactory.h>
#include <CAutomate.h>
#include <CSequenceur.h>
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

    const QList<CSequenceur::CyclePair> cycles = CSequenceur::getInstance()->getCycles();
    QList<IVariable *> ivars;

    for (int i = 0; i < cycles.count(); ++i) {
        const CSequenceur::CyclePair &pair = cycles[i];
        ICycle *cycle = pair.first;
        Q_ASSERT(cycle);
        IVariable *ivar = CVariableFactory::buildTemporary(QString::number(i), cycle->getLbl(), type_string);
        m_internalVariables[cycle->getName()] = ivar;
        ivars << ivar;
    }

    IConfiguratorUIHandler::layout(ivars, true);
}

IVariable *ConfiguratorSequencerUIHandler::getVariable(const QString &name)
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
    const int index = layoutRow(row);
    const CSequenceur::CyclePair pair = CSequenceur::getInstance()->getCycleAt(index);
    row.widgetAt<CPushButton *>(0)->setText(ivar->getLabel());
    row.widgetAt<CPushButton *>(2)->setText(QString::number(pair.second));
}

void ConfiguratorSequencerUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    const int index = layoutRow(row);
    CSequenceur *sequencer = CSequenceur::getInstance();
    sequencer->removeAt(index);
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
    const int row = layoutRow(qobject_cast<QWidget *>(sender()));
    CAutomate *automate = CAutomate::getInstance();
    CSequenceur *sequencer = CSequenceur::getInstance();
    CSequenceur::CyclePair pair = sequencer->getCycleAt(row);
    Q_ASSERT(pair.first);
    QString cycleName = pair.first->getName();

    if (!selectCycle(cycleName) || cycleName.isEmpty()) {
        return;
    }

    pair.first = automate->getCycle(cycleName);
    Q_ASSERT(pair.first);
    sequencer->replaceCycleAt(row, pair);
}

void ConfiguratorSequencerUIHandler::slotEditValueClicked()
{
    const int row = layoutRow(qobject_cast<QWidget *>(sender()));
    CSequenceur *sequencer = CSequenceur::getInstance();
    CSequenceur::CyclePair pair = sequencer->getCycleAt(row);
    Q_ASSERT(pair.first);
    int value = pair.second;

    if (!enterInteger(value) || value <= 0) {
        return;
    }

    pair.second = value;
    sequencer->replaceCycleAt(row, pair);
}
