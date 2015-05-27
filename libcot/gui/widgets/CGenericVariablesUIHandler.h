#ifndef CGENERICVARIABLESUIHANDLER_H
#define CGENERICVARIABLESUIHANDLER_H

#include "IVariableUIHandler.h"

class CGenericVariablesUIHandler : public IVariableUIHandler
{
    Q_OBJECT

public:
    explicit CGenericVariablesUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~CGenericVariablesUIHandler();

    virtual IVariable *getVariable(const QString &name) const Q_DECL_OVERRIDE;

    void layoutVariables(const QList<IVariable *> &variables, bool makeCopies);
    void applyProperties();

protected:
    QHash<QString, IVariable *> m_editedVariables;
    IVariablePtrList m_variables;
    IVariablePtrList m_variablesCopies;

private:
    void watchVariables(const IVariablePtrList &variables);
    void unwatchVariables(const IVariablePtrList &variables);

private slots:
    void slotVariableChanged();
};

#endif // CGENERICVARIABLESUIHANDLER_H
