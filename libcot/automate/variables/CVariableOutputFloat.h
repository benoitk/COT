#ifndef CVARIABLEOUTPUTFLOAT_H
#define CVARIABLEOUTPUTFLOAT_H

#include "CVariableFloat.h"
#include "IVariableOutput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableOutputFloat : public CVariableFloat, public IVariableOutput
{
    Q_OBJECT

public:
    CVariableOutputFloat(QObject *parent = Q_NULLPTR);
    CVariableOutputFloat(const QMap<QString, QVariant> &mapVar);
    ~CVariableOutputFloat();

//IVariableOutput
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    enumVariableOrganType getOrganType() const Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;

    void setValue(float) Q_DECL_OVERRIDE;
    using CVariableFloat::setValue;

    void writeValue() Q_DECL_OVERRIDE;

};

#endif // CVARIABLEOUTPUTFLOAT_H
