#ifndef IVARIABLE_H
#define IVARIABLE_H

#include <QVariant>
#include <QList>
#include "qmutex.h"

enum enumVariableType{
    e_type_bool = 0,
    e_type_float,
    e_type_int,
    e_type_string,
    e_type_stream,
    e_type_measure,
    e_type_list_variables,
    e_type_alarm,
    e_type_curve,
    e_type_unknow,
        // Internal to GUI
        type_mutable // a special variable used in gui which has an internal mutable custom type.
};

enum enumVariableAccess{
        e_access_read = 0,
        e_access_write,
        e_access_read_write
};

enum enumVariableOrganType {
    e_type_organ_none = 0,
    e_type_organ_input,
    e_type_organ_output,
};

class CUnit;
class CVariableMeasure;
class ICom;
class CAutomate;
//Interface pour toute les variables de l'automate
class IVariable : public QObject
{
    Q_OBJECT
    friend class CVariableFactory;
    friend class IVariableUIHandler;
    friend class IVariableObjectDescriber;

public:
    static int FLOAT_PRECISION;

    IVariable(CAutomate* arg_automate, QObject *parent);
    IVariable(const QVariantMap&, CAutomate* arg_automate, QObject* parent);
   // IVariable();
    virtual ~IVariable() {}
    virtual enumVariableOrganType getOrganType() const;
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
    virtual enumVariableType getType()const=0;
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

    virtual enumVariableAccess getAccess()const;
    virtual int getAddress()const;
    //qvariantmap can be converted to a json object
    virtual QVariantMap serialize();
    virtual void setRelatedStreamName(const QString &name) ;

    static QString typeToString(enumVariableType type);
    static QString organTypeToString(enumVariableOrganType type);

    virtual IVariable* getIVariable();
    virtual void initComs();

    bool operator<(IVariable*);
    bool operator>(IVariable*);

    virtual void setAddress(int address);
    virtual void setAccess(enumVariableAccess access);

    virtual CAutomate* getAutomate();
protected:

    template<typename T> T setValue(T arg_value, T arg_valueMin, T arg_valueMax){
        T resultValue;
        if(arg_valueMin == arg_valueMax || (arg_value >= arg_valueMin && arg_value <= arg_valueMax) )
            resultValue = arg_value;
        else if(arg_value < arg_valueMin)
            resultValue = arg_valueMin;
        else if(arg_value > arg_valueMax)
            resultValue = arg_valueMax;

            return resultValue;
        }



signals:
    void signalVariableChanged(IVariable*);

protected:

    void checkBindedVariable(QVariant var);
    int m_address;
    enumVariableAccess m_access;

    QString m_name;
    QString m_label;
    QList<IVariable*> m_listBinds;
    CUnit* m_unit;
    QMutex m_mutex;
    QList<ICom*> m_coms;

    CAutomate* m_automate;

};

// Typedefs
typedef IVariable* IVariablePtr;
typedef QList<IVariablePtr> IVariablePtrList;

#endif // IVARIABLE_H
