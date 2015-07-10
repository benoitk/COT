#ifndef CVARIABLEUNKNOW_H
#define CVARIABLEUNKNOW_H CVariableUnknow

#include "IVariable.h"

#include <qobject.h>

class CVariableUnknow : public IVariable
{
    Q_OBJECT

public:
    CVariableUnknow();
    CVariableUnknow(const QVariantMap&);
    ~CVariableUnknow();


    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    QVariant toVariant() Q_DECL_OVERRIDE;
    void setValue(bool);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;


private:

};

#endif // CVARIABLEUNKNOW_H
