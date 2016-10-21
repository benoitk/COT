#ifndef CVARIABLEMUTABLE_H
#define CVARIABLEMUTABLE_H

#include <QObject>
#include <QVariant>

#include "IVariable.h"

class CVariableMutable : public IVariable
{
    Q_OBJECT

public:
    enum Type {
        Undefined = -1,
        CycleType,
        Cycle,
        VariableType,
        VarOrganType,
        Unit,
        Extension,
        Organ,
        Stream,
        Format,
        Measure,
        Variable,
        Action,
        ActionType,
        StreamOrMeasure
    };

    explicit CVariableMutable(CAutomate* arg_automate, QObject *parent = 0);
    explicit CVariableMutable(const QVariantMap &data, CAutomate* arg_automate, QObject *parent = 0);
    explicit CVariableMutable(const QVariant &data, CAutomate* arg_automate, QObject *parent = 0);
    ~CVariableMutable();

    virtual enumVariableOrganType getOrganType() const;

    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    QVariant toVariant() Q_DECL_OVERRIDE;
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    virtual void setAccess(enumVariableAccess access) Q_DECL_OVERRIDE;

    CVariableMutable::Type mutableType() const;
    void setMutableType(CVariableMutable::Type mutableType);

private:
    QVariantMap m_data;
};

#endif // CVARIABLEMUTABLE_H
