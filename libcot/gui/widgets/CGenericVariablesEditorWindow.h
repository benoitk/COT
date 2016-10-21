#ifndef CGENERICVARIABLESEDITORWINDOW_H
#define CGENERICVARIABLESEDITORWINDOW_H

#include <QWidget>

class CGenericVariablesEditor;
class IVariable;
class QTabWidget;

typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;
class CAutomate;
class CGenericVariablesEditorWindow : public QWidget
{
    Q_OBJECT

public:
    typedef bool (*ValidatorFunc)(CGenericVariablesEditor *editor, void *userData1, void *userData2);
    explicit CGenericVariablesEditorWindow(CAutomate* arg_automate, QWidget *parent = 0);

    void setValidator(ValidatorFunc validator, void *userData1 = Q_NULLPTR, void *userData2 = Q_NULLPTR);
    void setVariables(const QString &title, const IVariablePtrList &variables, bool makeCopies);

private:
    QTabWidget *m_tabWidget;
    CGenericVariablesEditor *m_editor;

private slots:
    void slotOkTriggered();
    void slotCancelTriggered();

signals:
    void signalPropertiesApplied();
};

#endif // CGENERICVARIABLESEDITORWINDOW_H
