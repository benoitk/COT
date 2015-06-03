#ifndef CVARIABLEFLOAT_H
#define CVARIABLEFLOAT_H CVariableFloat

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableFloat : public IVariable
{
    Q_OBJECT

public:
    CVariableFloat(QObject *parent = Q_NULLPTR);
    CVariableFloat(float, int = 0, variableAccess =access_read);
    ~CVariableFloat();


    QVariant toVariant() Q_DECL_OVERRIDE;
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(float);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
protected:

    float m_fValeur;

};


#endif // CVARIABLEFLOAT_H
