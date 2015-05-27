#ifndef CGENERICVARIABLESEDITORWINDOW_H
#define CGENERICVARIABLESEDITORWINDOW_H

#include <QWidget>

class CGenericVariablesEditor;
class IVariable;
class QTabWidget;

typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;

class CGenericVariablesEditorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CGenericVariablesEditorWindow(QWidget *parent = 0);

    void setVariables(const QString &title, const IVariablePtrList &variables, bool makeCopies);

private:
    QTabWidget *m_tabWidget;
    CGenericVariablesEditor *m_editor;

private slots:
    void slotOkTriggered();
    void slotCancelTriggered();
};

#endif // CGENERICVARIABLESEDITORWINDOW_H
