#ifndef CVARIABLEBOOL_H
#define CVARIABLEBOOL_H

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableBool : public IVariable
{
    Q_OBJECT

public:
    CVariableBool(CAutomate* arg_automate, QObject *parent = Q_NULLPTR);
    CVariableBool(const QVariantMap&, CAutomate* arg_automate, QObject* parent);
    CVariableBool(CAutomate* arg_automate, QObject *parent,bool, int = 0, enumVariableAccess =e_access_read);
    ~CVariableBool();

    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    QVariant toVariant() Q_DECL_OVERRIDE;
    virtual void setValue(bool);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    using IVariable::getType;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
protected:


    bool m_value;
    bool m_defaultValue;

};
#endif // CVARIABLEBOOL_H
