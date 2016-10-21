#ifndef CVARIABLEFLOAT_H
#define CVARIABLEFLOAT_H CVariableFloat

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableFloat : public IVariable
{
    Q_OBJECT

public:
    CVariableFloat(CAutomate* arg_automate, QObject *parent);
    CVariableFloat(const QVariantMap& mapVar, CAutomate* arg_automate, QObject* parent);
    CVariableFloat(CAutomate* arg_automate, QObject *parent, float, int = 0, enumVariableAccess =e_access_read);
    ~CVariableFloat();


    QVariant toVariant() Q_DECL_OVERRIDE;
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    virtual void setValue(float);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    int getPrecision();
protected:

    float m_value;
    float m_valueMin;
    float m_valueMax;
    int m_precision;

};


#endif // CVARIABLEFLOAT_H
