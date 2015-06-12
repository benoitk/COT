#include "IConfiguratorUIHandler.h"
#include "CToolButton.h"
#include "StyleRepository.h"

IConfiguratorUIHandler::IConfiguratorUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IVariableUIHandler(scrollable, parent)
{
}

CToolButton *IConfiguratorUIHandler::newDeleteButton(IVariable *ivar)
{
    CToolButton *editor = new CToolButton(CToolButton::Delete);
    editor->setFixedSize(StyleRepository::configuratorButtonSize());
    editor->setUserData(ivar->getName());
    editor->setText(ivar->toString());
    connect(editor, &CToolButton::clicked, this, &IConfiguratorUIHandler::slotDeleteClicked);
    return editor;
}

void IConfiguratorUIHandler::rowAboutToBeDeleted(const Row &row, IVariable *ivar)
{
    Q_UNUSED(row);
    Q_UNUSED(ivar);
}

void IConfiguratorUIHandler::rowDeleted(const QString &name)
{
    Q_UNUSED(name);
}

void IConfiguratorUIHandler::slotDeleteClicked()
{
    CToolButton *editor = qobject_cast<CToolButton *>(sender());
    const QString name = editor->userData().toString();
    Row *row = getRow(name);

    if (!row) {
        Q_ASSERT(false);
        return;
    }

    IVariable *ivar = getVariable(name);
    Q_ASSERT(ivar);

    rowAboutToBeDeleted(*row, ivar);
    removeRow(name);
    rowDeleted(name);
}
