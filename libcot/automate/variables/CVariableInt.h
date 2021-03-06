#ifndef CInt_H
#define CInt_H

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInt : public IVariable
{
    Q_OBJECT

public:
    CVariableInt(CAutomate* arg_automate, QObject *parent = Q_NULLPTR);
    CVariableInt(const QVariantMap& mapVar, CAutomate* arg_automate, QObject * parent);
    CVariableInt(CAutomate* arg_automate, QObject *parent, int, int address = 0, enumVariableAccess =e_access_read);
    ~CVariableInt();


    QVariant toVariant() Q_DECL_OVERRIDE;
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    virtual void setValue(int iValeur);
    void setValue(const QVariant & value) Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;

protected:

    int m_value;
    int m_valueMin;
    int m_valueMax;
};

#endif // CInt_H
