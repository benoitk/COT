#ifndef CVARIABLEOUTPUTINT_H
#define CVARIABLEOUTPUTINT_H

#include "CVariableInt.h"
#include "IVariableOutput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableOutputInt : public CVariableInt, public IVariableOutput
{
    Q_OBJECT

public:
    CVariableOutputInt(QObject *parent = Q_NULLPTR);
    CVariableOutputInt(const QMap<QString, QVariant> &mapVar);
    ~CVariableOutputInt();

//IVariableOutput
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    VariableOrganType getOrganType() const Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;

    void setValue(float);
    using CVariableInt::setValue;

private:

    void writeValue();
};

#endif // CVARIABLEOUTPUTINT_H
