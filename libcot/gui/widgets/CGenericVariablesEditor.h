#ifndef CGENERICVARIABLESEDITOR_H
#define CGENERICVARIABLESEDITOR_H

#include "IScrollableUIWidget.h"

class CGenericVariablesUIHandler;
class IVariable;

typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;

class CGenericVariablesEditor : public IScrollableUIWidget
{
    Q_OBJECT

public:
    explicit CGenericVariablesEditor(QWidget *parent = Q_NULLPTR);

    void setVariables(const IVariablePtrList &variables, bool makeCopies);

    void applyProperties();

private:
    CGenericVariablesUIHandler *m_handler;

signals:
    void signalPropertiesApplied();
};

#endif // CGENERICVARIABLESEDITOR_H
