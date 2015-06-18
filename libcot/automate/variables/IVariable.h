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

class CUnit;
class CVariableMeasure;

//Interface pour toute les variables de l'automate
class IVariable : public QObject
{
    Q_OBJECT
    friend class CVariableFactory;
    friend class IVariableUIHandler;
    friend class IVariableObjectDescriber;

public:
    static int FLOAT_PRECISION;

    IVariable(QObject *parent);
    IVariable(const QVariantMap&);
    IVariable();
    virtual ~IVariable() {}
    virtual VariableOrganType getOrganType() const;
    virtual QVariant toVariant()=0;
    virtual QString toString()=0;
    virtual int toInt()=0;
    virtual float toFloat() =0;
    virtual bool toBool()=0;
    virtual QString getLabel()const ;
    virtual QString getName()const;
    virtual void setName(const QString&);
    virtual void setLabel(const QString &);
    virtual void setValue(const QVariant &)=0;
    virtual void addBind(IVariable*);
    virtual void delBind(IVariable*);
    virtual void setToBindedValue(const QVariant &)=0;
    virtual variableType getType()const=0;
    virtual void switchToUnit(CUnit*)=0;
    virtual CUnit *getUnit() const;
    virtual bool isStreamRelated()const;
    virtual QString getRelatedStreamName()const;
    virtual bool isMeasureRelated()const;
    QString getRelatedMeasureName() const;
    CVariableMeasure *getRelatedMeasure() const;
    virtual bool isDisplay()const;
    virtual QList<IVariable*> getListOutBinds()const;
    virtual QList<IVariable*> getListInBinds()const;

    virtual void setListOutBinds(const QList<IVariable*> &);
    virtual void setListInBinds(const QList<IVariable*> &) ;

    virtual variableAccess getAccess()const;
    virtual int getAddress()const;
    //qvariantmap can be converted to a json object
    virtual QVariantMap serialise()=0;
    virtual void setRelatedStreamName(const QString &name) ;

    static QString typeToString(variableType type);
    static QString organTypeToString(VariableOrganType type);

    virtual IVariable* getIVariable();

private:
    virtual void setAccess(variableAccess access);
    virtual void setAddress(int address);

signals:
    void signalVariableChanged(); // SERES_TODO: handle it in each variable (COT-64)

protected:
    int m_address;
    variableAccess m_access;

    QString m_name;
    QString m_label;
    QList<IVariable*> m_listBinds;
    CUnit* m_unit;
};

// Typedefs
typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;

#endif // IVARIABLE_H
