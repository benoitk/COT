#ifndef IVARIABLEOBJECTDESCRIBER_H
#define IVARIABLEOBJECTDESCRIBER_H

#include <QObject>
#include "cot_global.h"
#include "CVariableFactory.h"

class IVariableUIHandler;

/*
 * This class is responsable to generate a list of IVariable representing the properties
 * of an editable object like ICycle, IAction...
 * It do track variable for you and will delete them itself.
 * That's usefull to give or append to variables passed to an IVariableUIHandler.
 * */
class LIBCOT_EXPORT IVariableObjectDescriber : public QObject
{
    Q_OBJECT

public:
    explicit IVariableObjectDescriber(IVariableUIHandler *parent);
    virtual ~IVariableObjectDescriber();

    IVariablePtrList getVariables() const;
    IVariablePtr getVariable(const QString &name) const;
    void clear();

    virtual void describe(const QVariant &object) = 0;

protected:
    void setVariables(IVariablePtrList variables);

protected slots:
    void slotVariableChanged();

private:
    QHash<QString, IVariablePtr> m_variablesHash;
    IVariablePtrList m_variables;

signals:
    void signalVariableChanged(const QString &name);
};

// ICycle Describer
class CVariableICycleDescriber : public IVariableObjectDescriber
{
public:
    explicit CVariableICycleDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};


// IVariable Describer
class CVariableIVariableDescriber : public IVariableObjectDescriber
{
public:
    explicit CVariableIVariableDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};


// IAction Describer
class CVariableIActionDescriber : public IVariableObjectDescriber
{
public:
    explicit CVariableIActionDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};

#endif // IVARIABLEOBJECTDESCRIBER_H
