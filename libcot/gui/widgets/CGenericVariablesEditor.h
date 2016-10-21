#ifndef CGENERICVARIABLESEDITOR_H
#define CGENERICVARIABLESEDITOR_H

#include "IScrollableUIWidget.h"

class CGenericVariablesUIHandler;
class IVariable;

typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;
class CAutomate;
class CGenericVariablesEditor : public IScrollableUIWidget
{
    Q_OBJECT

public:
    typedef bool (*ValidatorFunc)(CGenericVariablesEditor *editor, void *userData1, void *userData2);
    explicit CGenericVariablesEditor(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);

    IVariable *getVariable(const QString &name) const;

    void setValidator(ValidatorFunc validator, void *userData1 = Q_NULLPTR, void *userData2 = Q_NULLPTR);
    void setVariables(const IVariablePtrList &variables, bool makeCopies);

    bool applyProperties();

private:
    CGenericVariablesUIHandler *m_handler;
    ValidatorFunc m_validator;
    void *m_userData1;
    void *m_userData2;

signals:
    void signalPropertiesApplied();
};

#endif // CGENERICVARIABLESEDITOR_H
