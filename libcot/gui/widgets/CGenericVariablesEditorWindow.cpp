#include "CGenericVariablesEditorWindow.h"
#include "CGenericVariablesEditor.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"

#include <QVBoxLayout>
#include <QAction>
#include <QTabWidget>

CGenericVariablesEditorWindow::CGenericVariablesEditorWindow(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget(this))
    , m_editor(new CGenericVariablesEditor(this))
{
    QVBoxLayout *vl = new QVBoxLayout(this);
    vl->addWidget(m_tabWidget);

    m_tabWidget->addTab(m_editor, QString());

    CScrollableWidget *sw = m_editor->scrollableWidget();
    CVerticalButtonBar *vbb = m_editor->buttonBar();

    vbb->addAction(CToolButton::ScrollUp, sw->moveUp());
    vbb->addAction(CToolButton::ScrollDown, sw->moveDown());
    connect(vbb->addAction(CToolButton::Ok), &QAction::triggered, this, &CGenericVariablesEditorWindow::slotOkTriggered);
    connect(vbb->addAction(CToolButton::Cancel), &QAction::triggered, this, &CGenericVariablesEditorWindow::slotCancelTriggered);
}

void CGenericVariablesEditorWindow::setVariables(const QString &title, const IVariablePtrList &variables, bool makeCopies)
{
    m_tabWidget->setTabText(0, title);
    m_editor->setVariables(variables, makeCopies);
}

void CGenericVariablesEditorWindow::slotOkTriggered()
{
    m_editor->applyProperties();
    close();
}

void CGenericVariablesEditorWindow::slotCancelTriggered()
{
    close();
}
