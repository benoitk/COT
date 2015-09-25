#ifndef CVARIABLESTRING_H
#define CVARIABLESTRING_H

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

#include "cot_global.h"

class LIBCOT_EXPORT CVariableString : public IVariable
{
    Q_OBJECT

public:
    CVariableString(QObject *parent = Q_NULLPTR);
    CVariableString(const QVariantMap& mapVar);
    CVariableString(const QString&);
    ~CVariableString();

    QVariant toVariant() Q_DECL_OVERRIDE;
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(const QVariant & value) Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;

    void setValue(QString);

private:

    QString m_sValeur;

};


#endif // CVARIABLESTRING_H
