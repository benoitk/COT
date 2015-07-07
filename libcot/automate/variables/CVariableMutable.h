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
        Unit,
        Extension,
        Organ,
        Stream,
        Format,
        Measure,
        Variable,
        Action,
        ActionType
    };

    explicit CVariableMutable(QObject *parent = 0);
    explicit CVariableMutable(const QVariantMap &data, QObject *parent = 0);
    explicit CVariableMutable(const QVariant &data, QObject *parent = 0);
    ~CVariableMutable();

    virtual VariableOrganType getOrganType() const;

    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    QVariant toVariant() Q_DECL_OVERRIDE;
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;


    CVariableMutable::Type mutableType() const;
    void setMutableType(CVariableMutable::Type mutableType);

private:
    QVariantMap m_data;
};

#endif // CVARIABLEMUTABLE_H
