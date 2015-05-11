#include "IConfiguratorUIHandler.h"
#include "CToolButton.h"

IConfiguratorUIHandler::IConfiguratorUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IVariableUIHandler(scrollable, parent)
{
}

CToolButton *IConfiguratorUIHandler::newDeleteButton(IVariable *ivar)
{
    CToolButton *editor = new CToolButton(CToolButton::Delete);
    editor->setFixedSize(21, 21);
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

void IConfiguratorUIHandler::deleteVariable(const QString &name)
{
    Q_UNUSED(name);
}

void IConfiguratorUIHandler::slotDeleteClicked()
{
    CToolButton *editor = qobject_cast<CToolButton *>(sender());
    const QString name = editor->userData().toString();

    if (!m_rows.contains(name)) {
        Q_ASSERT(false);
        return;
    }

    IVariable *ivar = getVariable(name);
    Q_ASSERT(ivar);

    const Row &row = m_rows[name];
    rowAboutToBeDeleted(row, ivar);

    qDeleteAll(row.widgets);
    m_rows.remove(name);
    deleteVariable(name);
}
