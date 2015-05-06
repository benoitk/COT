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
    };

    explicit CVariableMutable(QObject *parent = 0);
    explicit CVariableMutable(const QVariantMap &data, QObject *parent = 0);
    explicit CVariableMutable(const QVariant &data, QObject *parent = 0);
    ~CVariableMutable();

    virtual VariableOrganType getOrganType() const;
    virtual QString toString() Q_DECL_OVERRIDE;
    virtual int toInt() Q_DECL_OVERRIDE;
    virtual float toFloat()  Q_DECL_OVERRIDE;
    virtual bool toBool() Q_DECL_OVERRIDE;
    virtual QString getLabel()const  Q_DECL_OVERRIDE;
    virtual QString getName()const Q_DECL_OVERRIDE;
    virtual void setName(const QString&) Q_DECL_OVERRIDE;
    virtual void setLabel(const QString &) Q_DECL_OVERRIDE;
    virtual void setValue(const QVariant &) Q_DECL_OVERRIDE;
    virtual void addBind(IVariable*) Q_DECL_OVERRIDE;
    virtual void delBind(IVariable*) Q_DECL_OVERRIDE;
    virtual void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    virtual variableType getType()const Q_DECL_OVERRIDE;
    virtual void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    virtual CUnit *getUnit() const Q_DECL_OVERRIDE;
    virtual bool isStreamRelated()const Q_DECL_OVERRIDE;
    virtual QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    virtual bool isMeasureRelated()const Q_DECL_OVERRIDE;
    virtual QString getRelatedMeasureName()const Q_DECL_OVERRIDE;
    virtual bool isDisplay()const Q_DECL_OVERRIDE;
    virtual QList<IVariable*> getListOutBinds()const Q_DECL_OVERRIDE;
    virtual QList<IVariable*> getListInBinds()const Q_DECL_OVERRIDE;
    virtual variableAccess getAccess()const  Q_DECL_OVERRIDE;
    virtual int getAddress()const  Q_DECL_OVERRIDE;
    //qvariantmap can be converted to a json object
    virtual QVariantMap serialise() Q_DECL_OVERRIDE;

    QVariant toVariant() const;
    void setAccess(variableAccess access);

    CVariableMutable::Type mutableType() const;
    void setMutableType(CVariableMutable::Type mutableType);

private:
    QVariantMap m_data;
};

#endif // CVARIABLEMUTABLE_H
