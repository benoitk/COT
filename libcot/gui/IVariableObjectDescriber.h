#ifndef IVARIABLEOBJECTDESCRIBER_H
#define IVARIABLEOBJECTDESCRIBER_H

#include <QObject>
#include "cot_global.h"
#include "CVariableFactory.h"

class IVariableUIHandler;

/*
 * This class is responsible for generating a list of IVariable representing the properties
 * of an editable object like ICycle, IAction...
 * It tracks the variables for you and will delete them itself.
 * This is useful to generate variables passed to an IVariableUIHandler.
 */
class LIBCOT_EXPORT IVariableObjectDescriber : public QObject
{
    Q_OBJECT

public:
    explicit IVariableObjectDescriber(IVariableUIHandler *parent);
    virtual ~IVariableObjectDescriber();

    IVariablePtrList getVariables() const;
    // currently unused QHash<QString, IVariablePtr> getVariablesHash() const;
    IVariablePtr getVariable(const QString &name) const;
    bool hasValue(const QVariant &value) const;
    void clear();

    /// Subclasses reimplement this to create the list of variables, by calling setVariables.
    virtual void describe(const QVariant &object) = 0;

protected:
    void setVariables(IVariablePtrList variables);
    void setVariableAccess(IVariable *ivar, int access);

protected slots:
    void slotVariableChanged();

private:
    QHash<QString, IVariablePtr> m_variablesHash;
    IVariablePtrList m_variables;

signals:
    void signalVariableChanged(const QString &name);
};

// ICycle Describer, to edit one cycle
class CVariableICycleDescriber : public IVariableObjectDescriber
{
    Q_OBJECT

public:
    explicit CVariableICycleDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};

// IVariable Describer, to edit one variable
class CVariableIVariableDescriber : public IVariableObjectDescriber
{
    Q_OBJECT

public:
    explicit CVariableIVariableDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};

// IVariable Out Binds Describer, to edit one variable
class CVariableIVariableOutBindsDescriber : public IVariableObjectDescriber
{
    Q_OBJECT

public:
    explicit CVariableIVariableOutBindsDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};

// IVariable In Binds Describer, to edit one variable
class CVariableIVariableInBindsDescriber : public IVariableObjectDescriber
{
    Q_OBJECT

public:
    explicit CVariableIVariableInBindsDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};

// IAction Describer, to edit one action
class CVariableIActionDescriber : public IVariableObjectDescriber
{
    Q_OBJECT

public:
    explicit CVariableIActionDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};

// CStep Describer, to edit one step
class CVariableCStepDescriber : public IVariableObjectDescriber
{
    Q_OBJECT

public:
    explicit CVariableCStepDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;
};

// CStep action Describer, to edit one step actions
class CVariableCStepActionsDescriber : public IVariableObjectDescriber
{
    Q_OBJECT

public:
    explicit CVariableCStepActionsDescriber(IVariableUIHandler *parent);
    void describe(const QVariant &object) Q_DECL_OVERRIDE;

    QStringList getActionList() const;
};

#endif // IVARIABLEOBJECTDESCRIBER_H
