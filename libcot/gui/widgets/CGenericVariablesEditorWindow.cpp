#include "CGenericVariablesEditorWindow.h"
#include "CGenericVariablesEditor.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"

#include <QVBoxLayout>
#include <QAction>
#include <QTabWidget>

CGenericVariablesEditorWindow::CGenericVariablesEditorWindow(CAutomate* arg_automate, QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget(this))
    , m_editor(new CGenericVariablesEditor(arg_automate, this))
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
    connect(m_editor, &CGenericVariablesEditor::signalPropertiesApplied, this, &CGenericVariablesEditorWindow::signalPropertiesApplied);
}

void CGenericVariablesEditorWindow::setValidator(CGenericVariablesEditorWindow::ValidatorFunc validator, void *userData1, void *userData2)
{
    m_editor->setValidator(validator, userData1, userData2);
}

void CGenericVariablesEditorWindow::setVariables(const QString &title, const IVariablePtrList &variables, bool makeCopies)
{
    m_tabWidget->setTabText(0, title);
    m_editor->setVariables(variables, makeCopies);
}

void CGenericVariablesEditorWindow::slotOkTriggered()
{
    if (m_editor->applyProperties()) {
        close();
    }
}

void CGenericVariablesEditorWindow::slotCancelTriggered()
{
    close();
}
