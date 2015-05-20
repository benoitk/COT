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
        Variable
    };

    explicit CVariableMutable(QObject *parent = 0);
    explicit CVariableMutable(const QVariantMap &data, QObject *parent = 0);
    explicit CVariableMutable(const QVariant &data, QObject *parent = 0);
    ~CVariableMutable();

    virtual VariableOrganType getOrganType() const;
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat()  Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    QString getLabel()const  Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    void setName(const QString&) Q_DECL_OVERRIDE;
    void setLabel(const QString &) Q_DECL_OVERRIDE;
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    void addBind(IVariable*) Q_DECL_OVERRIDE;
    void delBind(IVariable*) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    CUnit *getUnit() const Q_DECL_OVERRIDE;
    bool isStreamRelated()const Q_DECL_OVERRIDE;
    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    bool isMeasureRelated()const Q_DECL_OVERRIDE;
    QString getRelatedMeasureName()const Q_DECL_OVERRIDE;
    bool isDisplay()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListOutBinds()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListInBinds()const Q_DECL_OVERRIDE;
    void setListOutBinds(const QList<IVariable*> &) Q_DECL_OVERRIDE;
    void setListInBinds(const QList<IVariable*> &) Q_DECL_OVERRIDE;

    variableAccess getAccess()const  Q_DECL_OVERRIDE;
    int getAddress()const  Q_DECL_OVERRIDE;
    //qvariantmap can be converted to a json object
    QVariantMap serialise() Q_DECL_OVERRIDE;

    QVariant toVariant() const;

    CVariableMutable::Type mutableType() const;
    void setMutableType(CVariableMutable::Type mutableType);
    void setRelatedStreamName(const QString &variableName) Q_DECL_OVERRIDE;

private:
    QVariantMap m_data;

    void setAccess(variableAccess access) Q_DECL_OVERRIDE;
};

#endif // CVARIABLEMUTABLE_H
