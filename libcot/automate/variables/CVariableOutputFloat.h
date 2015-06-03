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

    QVariantMap serialise() Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;

    void setValue(float);

private:

    void writeValue() Q_DECL_OVERRIDE;

};

#endif // CVARIABLEOUTPUTFLOAT_H
