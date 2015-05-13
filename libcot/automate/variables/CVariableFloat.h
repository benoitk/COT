#ifndef CVARIABLEFLOAT_H
#define CVARIABLEFLOAT_H CVariableFloat

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableFloat : public IVariable
{
    Q_OBJECT
    friend class CVariableFactory;

public:
    CVariableFloat(QObject *parent);
    CVariableFloat(float, int = 0, variableAccess =access_read);
    CVariableFloat();
    ~CVariableFloat();


    QString getName()const Q_DECL_OVERRIDE;
    void setName(const QString&)Q_DECL_OVERRIDE;

    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(float);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    QString getLabel()const Q_DECL_OVERRIDE;
    void setLabel(const QString &) Q_DECL_OVERRIDE;
    //QString getName()const;
    void addBind(IVariable*) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    //
    void delBind(IVariable*) Q_DECL_OVERRIDE;
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

    QVariantMap serialise() Q_DECL_OVERRIDE;
    variableAccess getAccess()const Q_DECL_OVERRIDE;
    int getAddress()const Q_DECL_OVERRIDE;
    void setRelatedStreamName(const QString &variableName) Q_DECL_OVERRIDE;
private:

    int m_address;
    variableAccess m_access;
    float m_fValeur;
    QString m_name;
    QString m_label;
    QList<IVariable*> m_listBinds;
    CUnit* m_unit;

    void setAccess(variableAccess access);
    void setAddress(int address);
};


#endif // CVARIABLEFLOAT_H
