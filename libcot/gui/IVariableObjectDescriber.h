#ifndef IVARIABLEOBJECTDESCRIBER_H
#define IVARIABLEOBJECTDESCRIBER_H

#include <QObject>

#include "CVariableFactory.h"

class IVariableObjectDescriber : public QObject
{
public:
    IVariableObjectDescriber(QObject *parent = Q_NULLPTR);
    virtual ~IVariableObjectDescriber();

    IVariablePtrList getVariables() const;
    IVariablePtr getVariable(const QString &name) const;
    void clear();

    virtual void describe(const QVariant &object) = 0;

protected:
    QHash<QString, IVariablePtr> m_variablesHash;
    IVariablePtrList m_variables;
};

// ICycle Describer
class IVariableICycleDescriber : public IVariableObjectDescriber
{
public:
    virtual void describe(const QVariant &object) Q_DECL_OVERRIDE;
};

#endif // IVARIABLEOBJECTDESCRIBER_H
