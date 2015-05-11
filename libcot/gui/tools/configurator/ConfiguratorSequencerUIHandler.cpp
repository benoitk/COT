#include "ConfiguratorSequencerUIHandler.h"

#include <QLabel>
#include <CToolButton.h>
#include <CPushButton.h>
#include <CSequenceur.h>
#include <ICycle.h>
#include <CVariableString.h>


ConfiguratorSequencerUIHandler::ConfiguratorSequencerUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{

}

ConfiguratorSequencerUIHandler::~ConfiguratorSequencerUIHandler()
{

}

void ConfiguratorSequencerUIHandler::layout()
{
    const QList<ICycle *> listVar = CSequenceur::getInstance()->getListSequenceCyclesMesures();
    QList<IVariable *> variables;
    foreach (ICycle *cycle, listVar) {
        IVariable *variable = new CVariableString;
        variable->setName(cycle->getName());
        variable->setLabel(cycle->getLbl());
        variables << variable;
    }

    IConfiguratorUIHandler::layout(variables);
}

int ConfiguratorSequencerUIHandler::columnCount() const
{
    return 4;
}

QWidget *ConfiguratorSequencerUIHandler::createWidget(int column, IVariable *ivar)
{
    if (!ivar) {
        return Q_NULLPTR;
    }
    switch (column) {
    case 0:
        return newButton(ivar);
    case 1: {
        QLabel *lab = new QLabel(container());
        lab->setText(QStringLiteral("X"));
        return lab;
    }
    case 2:
        return newButton(ivar);
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
    row.widgetAt<CPushButton *>(0)->setText(ivar->getLabel());
    row.widgetAt<CPushButton *>(2)->setText(ivar->getLabel());
}

void ConfiguratorSequencerUIHandler::rowAboutToBeDeleted(const IVariableUIHandler::Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

CPushButton *ConfiguratorSequencerUIHandler::newButton(IVariable *ivar)
{
    //TODO fix me
    CPushButton *button = new CPushButton(container());
    connect(button, &CPushButton::clicked, this, &ConfiguratorSequencerUIHandler::slotEditClicked);
    button->setText(ivar->getLabel());
    button->setUserData(ivar->getName());
    return button;
}

void ConfiguratorSequencerUIHandler::slotEditClicked()
{
    //TODO customize it.
    const QString variableName = qobject_cast<CPushButton *>(sender())->userData().toString();
    emit editVariable(variableName);
}
