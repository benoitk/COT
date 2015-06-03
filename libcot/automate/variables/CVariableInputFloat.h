#ifndef CVARIABLEINPUTFLOAT_H
#define CVARIABLEINPUTFLOAT_H

#include "CVariableFloat.h"
#include "IVariableInput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInputFloat : public CVariableFloat, public IVariableInput
{
    Q_OBJECT

public:
    CVariableInputFloat(QObject *parent = Q_NULLPTR);
    CVariableInputFloat(const QMap<QString, QVariant> &mapVar);
    ~CVariableInputFloat();

    //IVariableInput
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    variableType getType()const Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;

private:


    IVariable* readValue() Q_DECL_OVERRIDE;

};

#endif // CVARIABLEINPUTFLOAT_H
