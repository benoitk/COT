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
    CVariableOutputInt(CAutomate* arg_automate, QObject *parent = Q_NULLPTR);
    CVariableOutputInt(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject* parent);
    ~CVariableOutputInt();

//IVariableOutput
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    enumVariableOrganType getOrganType() const Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;

    void setValue(int) Q_DECL_OVERRIDE;
    using CVariableInt::setValue;


    void writeValue();
};

#endif // CVARIABLEOUTPUTINT_H
