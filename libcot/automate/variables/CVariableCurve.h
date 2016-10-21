#ifndef CVARIABLECURVE_H
#define CVARIABLECURVE_H

#include "IVariable.h"

#include <qobject.h>


class CVariableCurve : public IVariable
{
    Q_OBJECT

public:
    CVariableCurve(CAutomate* arg_automate, QObject *parent = Q_NULLPTR);
    CVariableCurve(const QVariantMap&, CAutomate* arg_automate, QObject* parent);
    CVariableCurve(CAutomate* arg_automate, QObject *parent, bool, int = 0, enumVariableAccess =e_access_read);
    ~CVariableCurve();

    QList<QPair<float,float>>  getListCurve();
    float getLiearisedY(float arg_x);
    float getLiearisedX(float arg_y);

    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    QVariant toVariant() Q_DECL_OVERRIDE;
    virtual void setValue(float x, float y);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
protected:

    QList<QPair<float,float>> m_listCurve;
};

#endif // CVARIABLECURVE_H

