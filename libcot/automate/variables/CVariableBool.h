#ifndef CVARIABLEBOOL_H
#define CVARIABLEBOOL_H

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableBool : public IVariable
{
    Q_OBJECT

public:
    CVariableBool(QObject *parent = Q_NULLPTR);
    CVariableBool(bool, int = 0, variableAccess =access_read);
    ~CVariableBool();

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
protected:

    bool m_bValeur;

};
#endif // CVARIABLEBOOL_H
