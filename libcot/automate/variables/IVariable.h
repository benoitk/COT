#ifndef IVARIABLE_H
#define IVARIABLE_H

#include <QVariant>
#include <QList>

enum variableType{
        type_bool = 0,
        type_float,
        type_int,
        type_string,
        type_stream,
        type_measure,
        type_list_variables,
        type_unknow,
        // Internal to GUI
        type_mutable // a special variable used in gui which has an internal mutable custom type.
};

enum variableAccess{
        access_read = 0,
        access_write,
        access_read_write
};

enum VariableOrganType {
    VariableOrganTypeNone = 0,
    VariableOrganTypeInput,
    VariableOrganTypeOutput,
};

//Interface pour toute les variables de l'automate
class CUnit;
class IVariable : public QObject
{
    Q_OBJECT
    friend class CVariableFactory;
    friend class IVariableUIHandler;
    friend class IVariableObjectDescriber;

public:
    static int FLOAT_PRECISION;

    IVariable(QObject *parent);
    IVariable() {}
    virtual ~IVariable() {}
    virtual VariableOrganType getOrganType() const { return VariableOrganTypeNone; }
    virtual QVariant toVariant()=0;
    virtual QString toString()=0;
    virtual int toInt()=0;
    virtual float toFloat() =0;
    virtual bool toBool()=0;
    virtual QString getLabel()const =0;
    virtual QString getName()const=0;
    virtual void setName(const QString&)=0;
    virtual void setLabel(const QString &)=0;
    virtual void setValue(const QVariant &)=0;
    virtual void addBind(IVariable*)=0;
    virtual void delBind(IVariable*)=0;
    virtual void setToBindedValue(const QVariant &)=0;
    virtual variableType getType()const=0;
    virtual void switchToUnit(CUnit*)=0;
    virtual CUnit *getUnit() const=0;
    virtual bool isStreamRelated()const=0;
    virtual QString getRelatedStreamName()const=0;
    virtual bool isMeasureRelated()const=0;
    virtual QString getRelatedMeasureName()const=0;
    virtual bool isDisplay()const=0;
    virtual QList<IVariable*> getListOutBinds()const=0;
    virtual QList<IVariable*> getListInBinds()const=0;

    virtual void setListOutBinds(const QList<IVariable*> &) =0;
    virtual void setListInBinds(const QList<IVariable*> &) =0;

    virtual variableAccess getAccess()const =0;
    virtual int getAddress()const =0;
    //qvariantmap can be converted to a json object
    virtual QVariantMap serialise()=0;
    virtual void setRelatedStreamName(const QString &name) = 0;

    static QString typeToString(variableType type);
    static QString organTypeToString(VariableOrganType type);

private:
    virtual void setAccess(variableAccess access) = 0;
    virtual void setAddress(int address);

signals:
    void signalVariableChanged(); // SERES_TODO: handle it in each variable (COT-64)
};

// Typedefs
typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;

#endif // IVARIABLE_H
